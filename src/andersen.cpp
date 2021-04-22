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

        return false;
    }

  char andersen::ID = 0;
  RegisterPass<andersen> Y("basic-aa-custom", "Andersen's Analysis");
}
