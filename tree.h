//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.
*/

template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;
    vector<Node<U>*> parents;

    Node(const string &nodeID, const U &value)
        : id(nodeID), data(value) {
    }
};

template <typename T>
class Tree {
private:
    Node<T>* root;
    unordered_map<string, Node<T>*> nodesById;

    void deleteAllNodes() {
        for (auto &entry : nodesById) {
            delete entry.second;
        }
        nodesById.clear();
        root = nullptr;
    }

public:
    Tree() : root(nullptr) {
    }

    void createRoot(const string &id, const T &value) {
        if (root != nullptr) {
            return;
        }

        Node<T>* newRoot = new Node<T>(id, value);
        root = newRoot;
        nodesById[id] = newRoot;
    }

    void addNode(const string &parentID, const string &childID, const T &value) {
        Node<T>* parentNode = findNode(parentID);
        if (parentNode == nullptr) {
            return;
        }

        Node<T>* childNode = findNode(childID);
        if (childNode == nullptr) {
            childNode = new Node<T>(childID, value);
            nodesById[childID] = childNode;
        }

        for (Node<T>* existingChild : parentNode->children) {
            if (existingChild->id == childID) {
                return;
            }
        }

        parentNode->children.push_back(childNode);
        childNode->parents.push_back(parentNode);
    }

    Node<T>* findNode(const string &id) {
        auto it = nodesById.find(id);
        if (it == nodesById.end()) {
            return nullptr;
        }

        return it->second;
    }

    void printAll() {
        cout << "printAll() not fully implemented yet." << endl;
    }

    ~Tree() {
        deleteAllNodes();
    }
};

#endif //FA25EC3_TREE_H