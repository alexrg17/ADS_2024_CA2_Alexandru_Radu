#pragma once
#include "BSTNode.h"
#include <vector>
#include <stdexcept>
#include <functional>
#include <iostream>

template <class T>
class BinaryTree {
private:
    BSTNode<T>* root;

    // Helper function to destroy the tree recursively
    void destroyTree(BSTNode<T>* node) {
        if (node != nullptr) {
            destroyTree(node->getLeft());
            destroyTree(node->getRight());
            delete node;
        }
    }

public:
    // Constructor
    BinaryTree() : root(nullptr) {}

    // Copy Constructor
    BinaryTree(const BinaryTree<T>& other) : root(nullptr) {
        if (other.root != nullptr)
            root = new BSTNode<T>(*other.root);
    }

    // Assignment Operator
    BinaryTree<T>& operator=(const BinaryTree<T>& other) {
        if (this != &other) {
            clear();
            if (other.root != nullptr) {
                root = new BSTNode<T>(*other.root);
            }
        }
        return *this;
    }

    // Add a new item to the tree
    void add(const T& item) {
        if (root == nullptr) {
            root = new BSTNode<T>(item);
        } else {
            root->add(item);
        }
    }

    // Remove an item from the tree
    bool remove(const T& item) {
        if (!root) return false;

        BSTNode<T>* parent = nullptr;
        BSTNode<T>* current = root;

        // Search for the node to remove
        while (current && current->getItem() != item) {
            parent = current;
            current = item < current->getItem() ? current->getLeft() : current->getRight();
        }

        if (!current) return false; // Item not found

        // Node with at most one child
        if (!current->getLeft() || !current->getRight()) {
            BSTNode<T>* temp = current->getLeft() ? current->getLeft() : current->getRight();

            if (!parent) { // Removing the root node
                root = temp;
            } else if (parent->getLeft() == current) {
                parent->setLeft(temp);
            } else {
                parent->setRight(temp);
            }
            delete current;
        } else {
            // Node with two children
            BSTNode<T>* successor = current->getRight();
            while (successor->getLeft() != nullptr) {
                successor = successor->getLeft();
            }
            T successorData = successor->getItem();
            remove(successorData);
            current->setItem(successorData);
        }

        return true;
    }

    // Clear the entire tree
    void clear() {
        destroyTree(root);
        root = nullptr;
    }

    // Count the number of nodes in the tree
    int count() const {
        return root ? root->count() : 0;
    }

    // Find an item in the tree
    T* find(const T& item) const {
        BSTNode<T>* current = root;
        while (current) {
            if (current->getItem() == item) {
                return &current->getItem();
            }
            current = item < current->getItem() ? current->getLeft() : current->getRight();
        }
        return nullptr;
    }

    // Perform an in-order traversal of the tree and return a vector of items
    std::vector<T> inOrderTraversal() const {
        std::vector<T> result;
        std::function<void(BSTNode<T>*)> traverse = [&](BSTNode<T>* node) {
            if (node) {
                traverse(node->getLeft());
                result.push_back(node->getItem());
                traverse(node->getRight());
            }
        };
        traverse(root);
        return result;
    }

    // Utility to print the in-order traversal of the tree
    void printInOrder() const {
        auto result = inOrderTraversal();
        for (const auto& item : result) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // Destructor
    ~BinaryTree() {
        clear();
    }
};
