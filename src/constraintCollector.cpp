#include "../include/constraintCollector.h"

namespace llvm {

    void constraintCollector::getAnalysisUsage(AnalysisUsage &AU) const{


        AU.setPreservesAll();

    }

    bool constraintCollector::runOnModule(Module &M) { 

        // call helper functions to collect constraints

        globalConstraintCollector(M);

        for (Function &F : M)
            functionConstraintCollector(F);

        return false;
    }

    void constraintCollector::globalConstraintCollector(Module &M) {

        // get list of global variables
        for (auto &glob : M.getGlobalList()) {

            if (glob.getType()->isPointerTy()) {
                globalConstraints.insert(&glob);
            }
            
        } 

        // get list of functions
        for (auto &func: M.getFunctionList()) {

            // we only care about functions that have their address taken i.e f = &myFunc;

            globalConstraints.insert(&func);

        }

    }

    void constraintCollector::functionConstraintCollector(Function &F) {

        // populate constraintMaps with empty sets for the time being
        base.insert({&F, cSet()});
        simple.insert({&F, cSet()});
        complex1.insert({&F, cSet()});
        complex2.insert({&F, cSet()});
        functionCalls.insert({&F, cSet()});
        functionRet.insert({&F, cSet()});

        // traverse the function CFG (not important to traverse in any particular order)
        for (BasicBlock &B : F) {

            for (Instruction &I : B) {

                // we only care about instructions that are of pointer type
                switch (I.getOpcode()) {

                    case Instruction::Alloca:

                        // alloca always results in a pointer type so we don't need to check if return type is pointer type
                        base[&F].insert(&I);
                        break;
                    
                    case Instruction::Store:

                        // only insert if the src operand is of pointer type; format "store a, b" = " *a = b"
                        if (I.getOperand(0)->getType()->isPointerTy())
                            complex2[&F].insert(&I);
                        break;
                    
                    case Instruction::Load:

                        // only insert in constraints if a pointer is being loaded; format "a = load b" = "a = *b"
                        if (I.getType()->isPointerTy())
                            complex1[&F].insert(&I);
                        break;
                    
                    case Instruction::Call: {
                        Function *callee = dyn_cast<CallBase>(&I)->getCalledFunction();

                        // we only deal with user-defined functions
                        // Technically speaking, we shouldn't trust any library functions that take pointers as arguments but we let that slide for out implementation
                        if (callee->size() == 0)
                            break;

                        // only insert function calls that have pointer arguments or return a pointer type;
                        if (callee->getReturnType()->isPointerTy() || hasPtrArgs(*callee))
                            functionCalls[&F].insert(&I);
                        break;
                    }

                    case Instruction::Ret:{

                        // this is a special case for COPY. We treat it differently because it is important for interprocedural analysis

                        ReturnInst *ret = dyn_cast<ReturnInst>(&I);

                        // if return value is not null
                        if (Value *retVal = ret->getReturnValue()){

                            // if retVal is pointer Type
                            if (retVal->getType()->isPointerTy())
                                functionRet[&F].insert(&I);

                        }

                        break;

                    }
                    // we break both as copy "a=b" since our analysis is field insensitive. There can be more copy instructions in the IR but we only deal with these two for now
                    case Instruction::GetElementPtr:

                    case Instruction::BitCast:
                        simple[&F].insert(&I);

                                    
                    default:
                        break;
                }

            }
        }

    }

    bool constraintCollector::hasPtrArgs(Function &F) {

        /*
            return true if the function F has any args passed by ref
            populate function info with pointer Arguments

        */

    // iterator over the arguments of a function to determine if any is passed by ref

        bool hasPtr = false;

        for(Function::arg_iterator it = F.arg_begin(), itE = F.arg_end(); it != itE; ++it) {

            Argument *arg = &*it;

            // since C does not support passing by ref, we simply check if the arg is a pointerTy
            if (arg->getType()->isPointerTy()) {
                hasPtr = true;

            }

        }

        return hasPtr;
    }

  char constraintCollector::ID = 0;
  RegisterPass<constraintCollector> X("constraint-collector", "Constraint Collector for Andersen's Pointer Analysis");

}
