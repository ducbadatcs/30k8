
// COS30008, Problem Set 4, Problem 3, 2022

#pragma once

#include "BinarySearchTree.h"

#include <exception>
#include <stack>
#include <stdexcept>

template <typename T> class BinarySearchTreeIterator {
  private:
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode *;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree &fBSTree; // binary search tree
    BTNStack fStack;       // DFS traversal stack

    void pushLeft(BNode *aNode) {
        while (!aNode->empty()) {
            this->fStack.push(aNode);
            aNode = aNode->left;
        }
    };

  public:
    using Iterator = BinarySearchTreeIterator<T>;

    BinarySearchTreeIterator(const BinarySearchTree<T> &aBSTree)
        : fBSTree(aBSTree) {}

    const T &operator*() const {
        if (this->fStack.empty()) {
            throw std::out_of_range("Empty root");
        }
        return this->fStack.top()->key;
    }

    Iterator &operator++() {
        // if node has a left node, go into that node

        if (!this->fStack.empty()) {
            // travel root?
            BTreeNode current_root = this->fStack.top();
            this->fStack.pop();

            if (!current_root->right->empty()) {
                this->pushLeft(current_root->right);
            }
        }

        return *this;
    };

    Iterator operator++(int) {
        Iterator old = *this;
        ++(*this);
        return old;
    }
    bool operator==(const Iterator &aOtherIter) const {
        // check if two stacks are equal maybe?
        return ((this->fStack.empty() && aOtherIter.fStack.empty()) ||
                (this->fStack.size() == aOtherIter.fStack.size() &&
                 this->fStack.top()->key == aOtherIter.fStack.top()->key));
    };
    bool operator!=(const Iterator &aOtherIter) const {
        return !(*this == aOtherIter);
    };

    Iterator begin() const {
        // YOU CAN JUST DO THIS?
        Iterator it = Iterator(this->fBSTree);
        if (!this->fBSTree.empty()) {
            it.pushLeft(this->fBSTree.fRoot);
        }
        return it;
    };
    Iterator end() const { return Iterator(this->fBSTree); };
};
