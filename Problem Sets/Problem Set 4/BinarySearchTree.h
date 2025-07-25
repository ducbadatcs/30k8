
// COS30008, Problem Set 4, Problem 2, 2022

#pragma once

// #include "BinarySearchTreeIterator.h"
#include "BinaryTreeNode.h"

#include <stdexcept>

// Problem 3 requirement
template <typename T> class BinarySearchTreeIterator;

template <typename T> class BinarySearchTree {
  private:
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode *;

    BTreeNode fRoot;

  public:
    BinarySearchTree()
        : fRoot(&BNode::NIL) {

          };

    ~BinarySearchTree() {
        if (!this->fRoot->empty()) {
            delete this->fRoot;
        }
    };

    bool empty() const { return this->fRoot->empty(); };
    size_t height() const { return this->fRoot->height(); };

    bool insert(const T &aKey) {
        if (this->empty()) {
            this->fRoot = new BinaryTreeNode<T>(aKey);
            return true;
        }
        return this->fRoot->insert(aKey);
    }
    bool remove(const T &aKey) {
        if (this->empty()) {
            return false;
        }
        return this->fRoot->remove(aKey, this->fRoot);
    }

    // Problem 3 methods

    using Iterator = BinarySearchTreeIterator<T>;

    // Allow iterator to access private member variables
    friend class BinarySearchTreeIterator<T>;

    Iterator begin() const { return Iterator(*this).begin(); }
    Iterator end() const { return Iterator(*this).end(); }
};
