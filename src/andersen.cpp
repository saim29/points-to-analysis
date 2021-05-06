#include "../include/andersen.h"

namespace llvm {

    // commandline arguments
    cl::opt<bool> interprocedural ("interprocedural", cl::desc("Run across functions"));
    cl::opt<bool> printSets ("print-pts-to-sets", cl::desc("Print sets to stderr"));

    void andersen::getAnalysisUsage(AnalysisUsage &AU) const {

        // run the constraint collector pass before this one
        AU.addRequired<constraintCollector>();
        AU.setPreservesAll();
    }

    bool andersen::runOnModule(Module &M) {

        // this builds the points-to-graph of every function in M using constraintCollector and constraintGraph classes
        // Note that our implementation does not handle used uninitialized pointers since they point to garbage
        // pointers must be assigned some memory location before they are used

        // collect all required constraints 
        constraintCollector &constraints = getAnalysis<constraintCollector>();

        // populate graph
        errs() << "Initializing Graph ...";
        initConstraintGraph(constraints.base, constraints.simple, constraints.complex1, constraints.globalConstraints);
        errs() << " Initialized!!!\n";
        // solve the graph iteratively
        errs() << "Solving Graph ... \n";
        solveConstraintGraph(constraints.complex1, constraints.complex2, constraints.functionCalls, constraints.functionRet);
        errs() << " Solved!!!\n";
        // compute poiints-to set for every graph node
        PointsToSets pSets = points_to_graph.computePointsToSets();

        // if flag is set only then print sets, otherwise ignore
        if (printSets) {
            // print points-to sets
            errs() << "\n\nPoints to sets:";
            for(auto node : pSets) {

                errs() << "\n\n--------------------------\n";
                errs() << "Set for: "<< node.first->nodeTy << " ";
                if (Function *func = dyn_cast<Function>(node.first->ref)) {
                    errs() << func->getName() << "\n";
                } else {
                    node.first->ref->dump();
                }
                errs() << "--------------------------\n";

                for (auto child : node.second) {

                    errs() << "Node Ref: " << child->nodeTy << " ";
                    if (Function *child_func = dyn_cast<Function>(child->ref)) {
                        errs() << child_func->getName() << "\n";
                    } else {
                        child->ref->dump();
                    }
                } 
            }
        }

        return false;
    }

    void andersen::initConstraintGraph(DenseMap<Function*, cSet> base, DenseMap<Function*, cSet> simple, 
        DenseMap<Function*, cSet> loads, DenseSet<GlobalValue*> global) {

        // add constraints for all global placeholders e.g functions and global variables
        for(GlobalValue* constraint : global) {
            
            if (GlobalVariable *gv = dyn_cast<GlobalVariable>(constraint)) {

                // if the pointer points to a mem location then it is a leaf in our graph i.e node with no children
                // otherwise if it points to a pointer then it can potentially point to other things
                // SSA is immutable hence we can map pointers that point to mem locations as mem locations only
                // this makes our analysis easier
                if (gv->getType()->getContainedType(0)->isPointerTy()) 
                    points_to_graph.addNode(constraint, NodeType::PTR);
                else 
                    points_to_graph.addNode(constraint, NodeType::MEM);

            } else if (Function *f = dyn_cast<Function>(constraint)) {

                // global functions can only be mem since we cannot create a function without a mem placeholder
                points_to_graph.addNode(constraint, NodeType::MEM);

                // add nodes for function arguments that are pointers
                for(Function::arg_iterator it = f->arg_begin(), itE = f->arg_end(); it != itE; ++it) {

                    Argument *arg = &*it;

                    if (arg->getType()->isPointerTy()) {
                        points_to_graph.addNode(arg, NodeType::PTR);
                    }
                }
            }
        }

        for(auto func: base) {

            for (auto alloc: func.second) {

                // if the pointer points to a mem location then it is a leaf in our graph i.e node with no children
                // otherwise if it points to a pointer then it can potentially point to other things
                if (alloc->getType()->getContainedType(0)->isPointerTy())
                    points_to_graph.addNode(alloc, NodeType::PTR);
                else 
                    points_to_graph.addNode(alloc, NodeType::MEM);

            }

        }

        // loads result in the creation of new nodes since they are assigned to new virtual registers
        for(auto func : loads) {

            for (auto load : func.second) {

                points_to_graph.addNode(load, NodeType::PTR);

            }

        }

        for(auto func: simple) {

            for (auto copy: func.second) {

                //copy can introduce new nodes in the graph if they are pointers; we don't care about copy introducing new MEM nodes
                if (copy->getType()->isPointerTy()) {
                    points_to_graph.addNode(copy, NodeType::PTR);
                }

                // get ptr nodes for specific values (copy is equating two pointers)
                Node* src = points_to_graph.getPtrNode(copy);
                Node* dst = points_to_graph.getPtrNode(copy->getOperand(0));

                // add an edge from src to children of dst
                for (auto child: dst->children)
                    points_to_graph.addEdge(src, child);
            }

        }

    }

    void andersen::solveConstraintGraph(DenseMap<Function*, cSet> complex1, DenseMap<Function*, cSet> complex2, 
        DenseMap<Function*, cSet> calls, DenseMap<Function*, cSet> rets) {

        // iterate over all constraints and keep applying them until the graph stops changing
        unsigned numIterations = 0;
        bool changed = false;

        do {

            changed = false;
            for (auto func : complex1) {

                for (auto constraint : func.second) {

                    Node* src = points_to_graph.getPtrNode(constraint->getOperand(0));
                    Node* dst = points_to_graph.getPtrNode(constraint);

                    // add an edge from dst to all children of src
                    unsigned bef = dst->children.size();
                    for (auto child: src->children) {

                        for (auto src_child : child->children)
                            points_to_graph.addEdge(dst, src_child);

                    }
                    unsigned af = dst->children.size();

                    changed = bef != af || changed;
                }
            }

            for (auto func: complex2) {

                for (auto constraint : func.second) {

                    Node* src = points_to_graph.getPtrNode(constraint->getOperand(0));
                    Node* dst = points_to_graph.getPtrNode(constraint->getOperand(1));

                    // add an edge from all children of dst to src

                    for (auto child: dst->children) {
                        
                        unsigned bef = child->children.size();
                        for (auto src_child : src->children) {
                            points_to_graph.addEdge(child, src_child);
                        }

                        unsigned af = child->children.size();

                        changed = bef != af || changed;

                    }

                }

            }

            // only do this if interprocedural flag is set
            if (interprocedural) {

                // we only deal with calls that involve pointer operands; We ignore all other calls; this is handled in constraintCollector
                for (auto func: calls) {
                    
                    // the graph for the function has already been built and initialized
                    // the graph for each function is a connected component currently
                    // we just need to add edges from the ptr args of the fucntion since passing an argument is equivalent to copy
                    // this is equivalent to connecting the points-to-graph of functions

                    for (auto call: func.second) {

                        // we do this as an initialization step for all calls; This is utilized for ret instructions that return a pointer
                        points_to_graph.addNode(call, NodeType::PTR);

                        CallBase *base = dyn_cast<CallBase>(call);
                        Function *callee_func = base->getCalledFunction();
                        std::vector<Function*> possibleFuncs;

                        if (callee_func == NULL) {
                            //get possible function calls
                            Value *func_ptr = base->getOperand(0);
                            Node *func_ptr_node = points_to_graph.getPtrNode(func_ptr);

                            if (func_ptr_node) {
                                for (auto child : func_ptr_node->children) {
                                    
                                    if (auto child_func = dyn_cast<Function>(child->ref))
                                        possibleFuncs.push_back(child_func);
                                }
                            }
                        } else {
                            possibleFuncs.push_back(callee_func);
                        }

                        for (Function *callee : possibleFuncs) {
                            std::vector<Value*> callArgs;
                            std::vector<Value*> funcArgs;

                            // go over all call instruction arguments and function arguments
                            for (int i=0; i<base->getNumArgOperands(); i++) {

                                // get corresponding call args and function args
                                Value *funcOp = callee->getArg(i);
                                Value *callOp = base->getArgOperand(i);

                                // only insert pointer arguments in vector
                                if (callOp->getType()->isPointerTy()) {

                                    funcArgs.push_back(funcOp);
                                    callArgs.push_back(callOp);

                                }
                            }

                            // add edges from function arg to children of call arg; similar to a = b, where a is the function arg and b is the passed arg

                            for (int i=0; i<funcArgs.size(); i++){

                                Node *src = points_to_graph.getPtrNode(callArgs[i]);
                                Node *dst = points_to_graph.getPtrNode(funcArgs[i]);

                                unsigned bef = dst->children.size();
                                for(auto child : src->children)
                                    points_to_graph.addEdge(dst, child);

                                unsigned af = dst->children.size();

                                changed = bef != af || changed;
                            }

                            // we only deal with return instructions that return a pointer. We do this for callee
                            for (auto ret : rets[callee]) {

                                // this is equivalent to a = retval; This is a special case for simple constraint. we add edges from a to children of retval;
                                Node* retNode = points_to_graph.getPtrNode(ret->getOperand(0));
                                Node* callNode = points_to_graph.getPtrNode(call);

                                unsigned bef = callNode->children.size();
                                for (auto child: retNode->children)
                                    points_to_graph.addEdge(callNode, child);

                                unsigned af = callNode->children.size();
                                changed = bef != af || changed;

                            }
                        }
                    }
                }
            }

            numIterations++;
        } while (changed);

        errs() << "Convergence: " << numIterations << "\n";
    }

    void andersen::addEdgeRecursive(Node *from, Node *to, bool constraint, DenseSet<Node*> &visited) {

        // if leaf node or node already visited
        if (visited.find(to) != visited.end() || to->nodeTy == MEM) {
            return ;
        }

        bool hasChanged = false;
        visited.insert(to);
        for (auto child : to->children) {

            addEdgeRecursive(from, child, constraint, visited);
            if (constraint) {
                points_to_graph.addEdge(from, child);
            }
            else {
                points_to_graph.addEdge(child, from);
            }

        }
    }

    char andersen::ID = 0;
    RegisterPass<andersen> Y("basic-aa-custom", "Andersen's Analysis");
}
