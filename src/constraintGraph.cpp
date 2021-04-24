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

    std::vector<Node*> constraintGraph::getNodeList(NodeType ty) {

        std::vector<Node*> graphNodes;

        if (ty == PTR) {

            for(auto node : ptr) {

                graphNodes.push_back(node.second);
            }

        } else if (ty == MEM){

            for(auto node : mem) {

                graphNodes.push_back(node.second);
            }
        }

        return graphNodes;
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

    void constraintGraph::addNode(Value *ref, NodeType nodeTy) {

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

            obj_node = new Node(ref, MEM);
            mem.insert({ref, obj_node});

        }

        // for memory allocations, add edge from ptr to mem obj
        if (ptr_node != NULL && obj_node != NULL) {

            addEdge(ptr_node, obj_node);

        }

    }

    void constraintGraph::addEdge(Node *src, Node *dst) {

        if (src->nodeTy == PTR)
            ptr[src->ref]->children.insert(dst);
        else 
            mem[src->ref]->children.insert(dst);

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

    PointsToSets constraintGraph::computePointsToSets() {

        PointsToSets pSet;
        std::set<Node*> visited;

        std::vector<Node*> nodes = getNodeList(PTR);

        for (auto memNode : getNodeList(MEM)) {

            nodes.push_back(memNode);
        }

        for (auto node : nodes) {

            for (auto child: node->children) {

                pSet[node].insert(child);
            }
        }

        return pSet;
    }
}
