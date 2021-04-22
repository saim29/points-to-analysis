#include "../include/constraintGraph.h"

namespace llvm {

    constraintGraph::constraintGraph() {

    }

    constraintGraph::~constraintGraph() {

        for(auto node : cGraph) {

            delete node.second;
        }

    }

    Node* constraintGraph::getNode(Value *ref) {

        return cGraph[ref];

    }

    Value* constraintGraph::addNode(Value *ref, NodeType nodeTy) {

        Node *node = new Node(ref, nodeTy);
        cGraph.insert({ref, node});
        return ref;
    }

    void constraintGraph::addEdge(Node *src, Node *dst) {

        cGraph[src->ref]->children.insert(dst);

    }

    bool constraintGraph::isPath(Node* src, Node* dst) {

        std::queue<Node*> node_queue;
        std::set<Node*> visited;

        node_queue.push(src);

        while (!node_queue.empty()) {

            Node *cur = node_queue.front();
            node_queue.pop();

            visited.insert(cur);

            for (auto child : cur->children) {

                if (visited.find(child) == visited.end()) {

                    node_queue.push(child);

                }

                if (child == dst) {

                    return true;

                }

            }

        }

        return false;
    }
}
