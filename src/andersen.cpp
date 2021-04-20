#include "../include/andersen.h"

namespace llvm {

    bool andersen::runOnModule(Module &M) {
        for(Function &F : M) {
            for(BasicBlock &B : F){
                for(Instruction &I : B) {

                    if(AllocaInst *aI = dyn_cast<AllocaInst>(&I)) {
                        outs() << aI << "\n";
                    }

                }
            }
        }
        return false;
    }
    void getAnalysisUsage(AnalysisUsage& AU) {
        AU.setPreservesAll();
    }

    char andersen::ID = 0;
    RegisterPass<andersen> X("Andersen", "ECE 5984 final andersen");
}
