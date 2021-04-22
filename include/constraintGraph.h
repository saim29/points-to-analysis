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

    enum NodeType {

        PTR,  
        MEM

    };

    struct Node {

        Node(Value *ref, NodeType nodeTy) {

            this->ref = ref;
            this->nodeTy = nodeTy;
        }

        Value *ref;
        NodeType nodeTy; 
        DenseSet<Node*> children;

    };

    class constraintGraph {

        public:

            constraintGraph();
            ~constraintGraph();

            Node* getNode(Value* ref);
            Value* addNode(Value *ref, NodeType nodeTy);
            void addEdge(Node* to, Node* from);
            bool isPath(Node* to, Node* from);

        private:

            DenseMap<Value*, Node*> cGraph;

    };
}

#endif
