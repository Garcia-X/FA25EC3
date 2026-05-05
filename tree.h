//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
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

    bool childAlreadyLinked(Node<T>* parentNode, const string &childID) const {
        for (Node<T>* child : parentNode->children) {
            if (child->id == childID) {
                return true;
            }
        }
        return false;
    }

    bool parentAlreadyLinked(Node<T>* childNode, const string &parentID) const {
        for (Node<T>* parent : childNode->parents) {
            if (parent->id == parentID) {
                return true;
            }
        }
        return false;
    }

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

        if (!childAlreadyLinked(parentNode, childID)) {
            parentNode->children.push_back(childNode);
        }

        if (!parentAlreadyLinked(childNode, parentID)) {
            childNode->parents.push_back(parentNode);
        }
    }

    Node<T>* findNode(const string &id) {
        auto it = nodesById.find(id);
        if (it == nodesById.end()) {
            return nullptr;
        }

        return it->second;
    }

    void printAll() {
        vector<string> ids;
        ids.reserve(nodesById.size());

        for (const auto &entry : nodesById) {
            ids.push_back(entry.first);
        }

        sort(ids.begin(), ids.end());

        cout << "\n===== Story Tree =====\n";
        for (const string &id : ids) {
            Node<T>* node = nodesById[id];

            cout << "Node " << node->id << ": " << node->data << "\n";

            if (node->children.empty()) {
                cout << "  Child -> (none)\n";
            } else {
                for (Node<T>* child : node->children) {
                    cout << "  Child -> " << child->id << "\n";
                }
            }

            cout << "\n";
        }
        cout << "======================\n";
    }

    void playGame() {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }

        Node<T>* current = root;

        cout << "\n===== Begin Adventure =====\n\n";

        while (true) {
            cout << current->data << "\n";

            if (current->children.empty()) {
                cout << "There are no further paths.\n";
                cout << "Your journey ends here.\n\n";
                cout << "===== Adventure Complete =====\n";
                return;
            }

            cout << "Choose your next action:\n";
            for (int i = 0; i < static_cast<int>(current->children.size()); i++) {
                cout << i + 1 << ". " << current->children[i]->data << "\n";
            }

            int selection;
            cout << "Selection: ";
            cin >> selection;

            while (selection < 1 || selection > static_cast<int>(current->children.size())) {
                cout << "Invalid choice. Try again: ";
                cin >> selection;
            }

            cout << "\n";
            current = current->children[selection - 1];
        }
    }

    ~Tree() {
        deleteAllNodes();
    }
};

#endif //FA25EC3_TREE_H