
// COS30008, Problem Set 4, Problem 1, 2022

#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T> struct BinaryTreeNode {
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode *;

    T key;
    BNode *left, *right;

    static BNode NIL;

    const T &findMax() const {
        if (empty()) {
            throw std::domain_error("Empty tree encountered.");
        }

        return right->empty() ? key : right->findMax();
    }

    const T &findMin() const {
        if (empty()) {
            throw std::domain_error("Empty tree encountered.");
        }

        return left->empty() ? key : left->findMin();
    }

    bool remove(const T &aKey, BTreeNode aParent) {
        BTreeNode x = this;
        BTreeNode y = aParent;

        while (!x->empty()) {
            if (aKey == x->key) {
                break;
            }

            y = x; // new parent

            x = aKey < x->key ? x->left : x->right;
        }

        if (x->empty()) {
            return false; // delete failed
        }

        if (!x->left->empty()) {
            const T &lKey = x->left->findMax(); // find max to left
            x->key = lKey;
            x->left->remove(lKey, x);
        } else {
            if (!x->right->empty()) {
                const T &lKey = x->right->findMin(); // find min to right
                x->key = lKey;
                x->right->remove(lKey, x);
            } else {
                if (y != &NIL) // y can be NIL
                {
                    if (y->left == x) {
                        y->left = &NIL;
                    } else {
                        y->right = &NIL;
                    }
                }

                delete x; // free deleted node
            }
        }

        return true;
    }

    // PS4 starts here

    // is nil supposed to be whatever it is before they invented nullptr?;

    // I love how the type aliasing makes thing MUCH MORE CONFUSING

    BinaryTreeNode() {
        this->left = &NIL;
        this->right = &NIL;
    }
    BinaryTreeNode(const T &aKey) {
        // copy constructor?
        this->key = aKey;
        this->left = &NIL;
        this->right = &NIL;
    };
    BinaryTreeNode(T &&aKey) {
        this->key = std::move(aKey);
        this->left = &NIL;
        this->right = &NIL;
    };

    ~BinaryTreeNode() {
        if (!this->left->empty()) {
            delete left;
        }
        if (!this->right->empty()) {
            delete right;
        }
    };

    bool empty() const { return this == &NIL; };
    bool leaf() const { return this->left == &NIL && this->right == &NIL; };
    size_t height() const {
        if (this->empty()) {
            throw std::domain_error("Empty tree encountered");
        } else if (this->leaf()) {
            return 0;
        } else {
            size_t t = 0;
            if (!this->left->empty()) {
                t = max(t, this->left->height() + 1);
            }
            if (!this->right->empty()) {
                t = max(t, this->right->height() + 1);
            }
            return t;
        }
    };

    bool insert(const T &aKey) {
        // auto node = new BinaryTreeNode(aKey);
        if (this->empty()) {
            return false;
        } else {
            auto node = this;
            while (!node->empty()) {
                if (aKey == node->key) {
                    return false;
                } else if (aKey < node->key) {
                    if (node->left->empty()) {
                        node->left = new BinaryTreeNode<T>(aKey);
                        return true;
                    } else {
                        node = node->left;
                    }
                } else if (aKey > node->key) {
                    if (node->right->empty()) {
                        node->right = new BinaryTreeNode<T>(aKey);
                        return true;
                    } else {
                        node = node->right;
                    }
                }
            }
            return false;
        }
    };
};

template <typename T> BinaryTreeNode<T> BinaryTreeNode<T>::NIL;
