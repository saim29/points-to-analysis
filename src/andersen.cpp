#include "../include/andersen.h"

namespace llvm {

    void andersen::getAnalysisUsage(AnalysisUsage &AU) const {

        AU.addRequired<constraintCollector>();
        AU.setPreservesAll();
    }

    bool andersen::runOnModule(Module &M) {

        // collect all required constraints 
        constraintCollector &constraints = getAnalysis<constraintCollector>();

        // populate graph
        initConstraintGraph(constraints.base, constraints.simple, constraints.complex1, constraints.globalConstraints);

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

                //copy can introduce new nodes in the graph if they are pointers; we don't care about copy introducing new MEM nodes because they can't doing to anything
                if (copy->getType()->isPointerTy()) {
                    points_to_graph.addNode(copy, NodeType::PTR);
                }

                // get nodes for specific values
                Node* src = points_to_graph.getNode(copy);
                Node* dst = points_to_graph.getNode(copy->getOperand(0));

                // add an edge from src to dst to signify that dst can be pointed to by src
                points_to_graph.addEdge(src, dst);
            }

        }

    }

    void andersen::solveConstraintGraph(DenseMap<Function*, cSet> complex1, DenseMap<Function*, cSet> complex2) {

    }


  char andersen::ID = 0;
  RegisterPass<andersen> Y("basic-aa-custom", "Andersen's Analysis");
}
