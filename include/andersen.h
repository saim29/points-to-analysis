
#ifndef __ANDERSEN_PTR_ANALYSIS__
#define __ANDERSEN_PTR_ANALYSIS__

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include  "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/IR/CFG.h"
#include "llvm/Pass.h"

// included for convenience
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/DerivedTypes.h"
#include <vector>


namespace llvm {

  class andersen : public ModulePass {

    public:

      andersen();
      static char ID;
      ~andersen();

      virtual void getAnalysisUsage(AnalysisUsage &AU);
      virtual bool runOnModule(Module &M);

  };
}

#endif
