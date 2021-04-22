#include "../include/constraintCollector.h"

namespace llvm {

    void constraintCollector::getAnalysisUsage(AnalysisUsage &AU) const{


        AU.setPreservesAll();

    }

    bool constraintCollector::runOnModule(Module &M) { 
        
        return false;
    }

    void constraintCollector::globalConstraintCollector(Module &M) {

        // get list of global variables
        for (auto &glob : M.getGlobalList()) {

            globalConstraints.insert(&glob);
            
        } 

        // get list of functions
        for (auto &func: M.getFunctionList()) {

            // we only care about functions that have their address taken i.e f = &myFunc;
            if (func.hasAddressTaken()) {

                globalConstraints.insert(&func);

            }

        }

    }

    void constraintCollector::functionConstraintCollector(Function &F) {

        base.insert({&F, cSet()});
        simple.insert({&F, cSet()});
        complex1.insert({&F, cSet()});
        complex2.insert({&F, cSet()});
        functionCalls.insert({&F, cSet()});

        for (BasicBlock &B : F) {

            for (Instruction &I : B) {

                switch (I.getOpcode()) {

                case Instruction::Alloca:
                    break;
                
                case Instruction::Store:
                    break;
                
                case Instruction::Load:
                    break;
                
                case Instruction::Call:
                    break;
                
                case Instruction::GetElementPtr:

                case Instruction::BitCast:
                                
                default:
                    break;
                }

            }
        }

    }

  char constraintCollector::ID = 0;
  RegisterPass<constraintCollector> X("constraint-collector", "Constraint Collector for Andersen's Pointer Analysis");

}
