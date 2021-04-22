#include "../include/andersen.h"

namespace llvm {


    andersen::andersen() : ModulePass(ID) {
    }

    andersen::~andersen() {
    }


    bool andersen::runOnModule(Module &M) {
        for(Function &F : M) {
            for(BasicBlock &B : F){
                for(Instruction &I : B) {
                    if(AllocaInst *aI = dyn_cast<AllocaInst>(&I)) {
                        outs() << I.getName() << "\n";

                    }

                }
            }
        }
        return false;
    }

    void andersen::getAnalysisUsage(AnalysisUsage& AU) {
        AU.setPreservesAll();
    }

    char andersen::ID = 0;
    RegisterPass<andersen> X("andersen", "ECE 5984 final andersen");
}
