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

    void constraintGraph::addEdge(Node *to, Node *from) {

        cGraph[to->ref]->children.insert(from);

    }

    bool constraintGraph::isPath(Node* to, Node* from) {

        std::queue<Node*> node_queue;
        std::set<Node*> visited;

        node_queue.push(from);

        while (!node_queue.empty()) {

            Node *cur = node_queue.front();
            node_queue.pop();

            visited.insert(cur);

            for (auto child : cur->children) {

                if (visited.find(child) == visited.end()) {

                    node_queue.push(child);

                }

                if (child == to) {

                    return true;

                }

            }

        }

        return false;
    }
}