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

    void andersen::initConstraintGraph(DenseMap<Function*, cSet> base, DenseMap<Function*, cSet> simple,
        DenseMap<Function*, cSet> global) {

    }

    void andersen::solveConstraintGraph(DenseMap<Function*, cSet> complex1, DenseMap<Function*, cSet> complex2) {

    }


  char andersen::ID = 0;
  RegisterPass<andersen> Y("basic-aa-custom", "Andersen's Analysis");
}
