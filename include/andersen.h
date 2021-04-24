
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

#include "llvm/Support/CommandLine.h"

namespace llvm {

  class andersen : public ModulePass {

    public:

      static char ID;
      andersen() : ModulePass(ID) {}

      virtual void getAnalysisUsage(AnalysisUsage &AU) const;
      virtual bool runOnModule(Module &M);

    private:

      // graph to store all points-to relations
      constraintGraph points_to_graph;

      // method to initialize initial constraint graph
      void initConstraintGraph(DenseMap<Function*, cSet> base, DenseMap<Function*, cSet> simple,
          DenseMap<Function*, cSet> loads, DenseSet<GlobalValue*> global);

      // an iterative solver for complex constraints
      void solveConstraintGraph(DenseMap<Function*, cSet> complex1, DenseMap<Function*, cSet> complex2,
        DenseMap<Function*, cSet> calls, DenseMap<Function*, cSet> rets);
      void addEdgeRecursive(Node *from, Node *to, bool constraint, DenseSet<Node*> &visited);

      // an iterative solver to add callInstruction constraints in our graph
      void addInterproceduralInfo(DenseMap<Function*, cSet> calls);

  };
}

#endif
