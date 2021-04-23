#include "../include/constraintGraph.h"

namespace llvm {

    constraintGraph::constraintGraph() {

    }

    constraintGraph::~constraintGraph() {

        for(auto node : ptr) {

            delete node.second;
        }

        for(auto node : mem) {

            delete node.second;
        }

    }

    Node* constraintGraph::getPtrNode(Value *ref) {

        if (ptr.find(ref) != ptr.end())
            return ptr[ref];
        
        return NULL;

    }

    Node* constraintGraph::getMemNode(Value *ref) {

        if (mem.find(ref) != mem.end())
            return mem[ref];
        
        return NULL;

    }

    Value* constraintGraph::addNode(Value *ref, NodeType nodeTy) {

        // we don't need a pointer node for functions

        Node *ptr_node = NULL;
        Node *obj_node = NULL;

        if (!isa<Function>(ref)) {

            // create a pointer object in our ptr graph
            ptr_node = new Node(ref, PTR);
            ptr.insert({ref, ptr_node});
        
        }

        // we only need to create a corresponding memory object for allocaInst or functions
        if (isa<AllocaInst>(ref) || isa<Function>(ref)) {

            if (nodeTy == PTR) {

                obj_node = new Node(ref, PTR);
                mem.insert({ref, obj_node});

            } else if (nodeTy == MEM) {

                obj_node = new Node(ref, MEM);
                mem.insert({ref, obj_node});

            }

        }

        // if both are allocated then add an edge from the pointer to its corresponding mem object
        if (ptr_node != NULL && obj_node != NULL) {

            addEdge(ptr_node, obj_node);
        }

        return ref;
    }

    void constraintGraph::addEdge(Node *src, Node *dst) {

        ptr[src->ref]->children.insert(dst);

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
