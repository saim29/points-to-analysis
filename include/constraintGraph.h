#ifndef __ANDERSEN_CONSTRAINT_GRAPH__
#define __ANDERSEN_CONSTRAINT_GRAPH__

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

// included for convenience
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/DerivedTypes.h"



namespace llvm {

    struct graphNode {

        DenseSet<Value*> points_to;
        DenseSet<graphNode*> siblings;

    };


    class constraintGraph {

        public:

            // constructors & destructors
            constraintGraph();
            ~constraintGraph();


        private:

            std::vector<graphNode*> graphNodes;

    };
}

#endif
