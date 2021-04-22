
#ifndef __ANDERSEN_PTR_ANALYSIS__
#define __ANDERSEN_PTR_ANALYSIS__

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "llvm/IR/Instructions.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/IR/CFG.h"
#include "llvm/Pass.h"

#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/DerivedTypes.h"

#include "constraintCollector.h"
#include "constraintGraph.h"

namespace llvm {

  class andersen : public ModulePass {

    public:

      static char ID;
      andersen() : ModulePass(ID) {}

      virtual void getAnalysisUsage(AnalysisUsage &AU) const;
      virtual bool runOnModule(Module &M);

    private:

      constraintGraph points_to_graph;

  };
}

#endif
