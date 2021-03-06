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

    typedef DenseSet<Node*> PointsToSet;
    typedef DenseMap<Node*, PointsToSet> PointsToSets;

    class constraintGraph {

        public:

            constraintGraph();
            ~constraintGraph();

            std::vector<Node*> getNodeList(NodeType ty);
            Node* getPtrNode(Value* ref);
            Node* getMemNode(Value* ref);
            void addNode(Value *ref, NodeType nodeTy);
            void addEdge(Node* src, Node* dst);
            bool isPath(Node* src, Node* dst);
            PointsToSets computePointsToSets();

        private:

            DenseMap<Value*, Node*> ptr;
            DenseMap<Value*, Node*> mem;

    };
}

#endif
