#pragma once
#include "BSTNode.h"
#include <vector>
#include <stdexcept>
#include <functional>

template <class T>
class BinaryTree {
private:
    BSTNode<T>* root;

    void destroyTree(BSTNode<T>* node) {
        if (node != nullptr) {
            destroyTree(node->getLeft());
            destroyTree(node->getRight());
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree<T>& other) : root(nullptr) {
        if (other.root != nullptr)
            root = new BSTNode<T>(*other.root);
    }

    BinaryTree<T>& operator=(const BinaryTree<T>& other) {
        if (this != &other) {
            clear();
            if (other.root != nullptr) {
                root = new BSTNode<T>(*other.root);
            }
        }
        return *this;
    }

    void add(const T& item) {
        if (root == nullptr) {
            root = new BSTNode<T>(item);
        } else {
            root->add(item);
        }
    }

    bool remove(const T& item) {
        if (!root) return false;
        BSTNode<T>* parent = nullptr;
        BSTNode<T>* current = root;

        while (current && current->getItem() != item) {
            parent = current;
            current = item < current->getItem() ? current->getLeft() : current->getRight();
        }

        if (!current) return false; // Item not found

        // Node with maximum one child
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

    void clear() {
        destroyTree(root);
        root = nullptr;
    }

    int count() const {
        return root ? root->count() : 0;
    }

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

    ~BinaryTree() {
        clear();
    }
};