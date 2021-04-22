#include "../include/constraintCollector.h"

namespace llvm {

    void constraintCollector::getAnalysisUsage(AnalysisUsage &AU) const{


        AU.setPreservesAll();

    }

    bool constraintCollector::runOnModule(Module &M) { 
        
        return false;
    }

    void globalConstraintCollector(Module &M) {

    }

    void functionConstraintCollector(Function &F) {

        
    }

  char constraintCollector::ID = 0;
  RegisterPass<constraintCollector> X("constraint-collector", "Constraint Collector for Andersen's Pointer Analysis");

}
