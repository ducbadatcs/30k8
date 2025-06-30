
// COS30008, List, Problem Set 3, 2022

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class List {
  private:
    // auxiliary definition to simplify node usage
    using Node = DoublyLinkedList<T>;

    Node *fRoot;   // the first element in the list
    size_t fCount; // number of elements in the list

  public:
    // auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

    ~List() // destructor - frees all nodes
    {
        while (fRoot != nullptr) {
            if (fRoot != &fRoot->getPrevious()) // more than one element
            {
                Node *lTemp =
                    const_cast<Node *>(&fRoot->getPrevious()); // select last

                lTemp->isolate(); // remove from list
                delete lTemp;     // free
            } else {
                delete fRoot; // free last
                break;        // stop loop
            }
        }
    }

    void remove(const T &aElement) // remove first match from list
    {
        Node *lNode = fRoot; // start at first

        while (lNode != nullptr) // Are there still nodes available?
        {
            if (**lNode == aElement) // Have we found the node?
            {
                break; // stop the search
            }

            if (lNode != &fRoot->getPrevious()) // not reached last
            {
                lNode = const_cast<Node *>(&lNode->getNext()); // go to next
            } else {
                lNode = nullptr; // stop search
            }
        }

        // At this point we have either reached the end or found the node.
        if (lNode != nullptr) // We have found the node.
        {
            if (fCount != 1) // not the last element
            {
                if (lNode == fRoot) {
                    fRoot =
                        const_cast<Node *>(&fRoot->getNext()); // make next root
                }
            } else {
                fRoot = nullptr; // list becomes empty
            }

            lNode->isolate(); // isolate node
            delete lNode;     // release node's memory
            fCount--;         // decrement count
        }
    }

    //////////////////////////////////////////////////////////////////
    //// PS3
    //////////////////////////////////////////////////////////////////

    // P1

    // default constructor
    List() {
        this->fRoot = nullptr;
        this->fCount = 0;
    }

    // Is list empty?
    bool empty() const { return this->fCount == 0 || this->fRoot == nullptr; }

    // list size
    size_t size() const { return this->fCount; };

    // adds aElement at front
    void push_front(const T &aElement) {
        Node *node = new Node(aElement);

        if (this->fRoot == nullptr) {
            this->fRoot = node;
        } else {
            this->fRoot = &this->fRoot->push_front(*node);
            // this->fRoot = node;
        }

        this->fCount += 1;
    }

    // return a forward iterator
    Iterator begin() const {
        return DoublyLinkedListIterator<T>(this->fRoot).begin();
    }

    // return a forward end iterator
    Iterator end() const {
        return DoublyLinkedListIterator<T>(this->fRoot).end();
    }

    // return a backwards iterator
    Iterator rbegin() const {
        return DoublyLinkedListIterator<T>(this->fRoot).rbegin();
    }

    // return a backwards end iterator
    Iterator rend() const {
        return DoublyLinkedListIterator<T>(this->fRoot).rend();
    }

    // P2
    // adds aElement at back
    void push_back(const T &aElement) {
        Node *node = new Node(aElement);

        if (this->fRoot == nullptr) {
            this->fRoot = node;
        } else {
            this->fRoot->push_front(*node);
        }

        this->fCount += 1;
    }

    // P3
    // list indexer
    const T &operator[](size_t aIndex) const {
        if (aIndex >= this->fCount) {
            throw std::out_of_range("aIndex out of range");
        }
        auto it = this->begin();
        for (size_t i = 0; i < aIndex; i++) {
            ++it;
        }
        return *it;
    }

    // P4

    // copy constructor
    List(const List &aOtherList) {
        // perform a deep copy of aOtherList, since assignment of
        // aOtherList.fRoot basically points to the same pointer
        this->fRoot = nullptr;
        this->fCount = 0;

        for (int i = 0; i < aOtherList.fCount; i++) {
            this->push_back(aOtherList[i]);
        }
    }

    // assignment operator
    List &operator=(const List &aOtherList) {
        this->fRoot = nullptr;
        this->fCount = 0;

        for (int i = 0; i < aOtherList.fCount; i++) {
            this->push_back(aOtherList[i]);
        }
        return *this;
    }

    // P5

    // move constructor
    List(List &&aOtherList) noexcept {
        this->fRoot = std::exchange(aOtherList.fRoot, nullptr);
        this->fCount = std::exchange(aOtherList.fCount, 0);
    }

    // move assignment operator
    List &operator=(List &&aOtherList) noexcept {
        // test
        this->fRoot = std::exchange(aOtherList.fRoot, nullptr);
        this->fCount = std::exchange(aOtherList.fCount, 0);

        return *this;
    }

    // move push_front
    // operate on lvalues, so we need to change them into rvalues first
    void push_front(T &&aElement) {
        Node *node = new Node(std::move(aElement));

        if (this->empty()) {
            this->fRoot = node;
        } else {
            this->fRoot = &this->fRoot->push_front(*node);
            // this->fRoot = node;
        }

        this->fCount += 1;
    }

    // move push_back
    // same idea
    void push_back(T &&aElement) {
        Node *node = new Node(std::move(aElement));

        if (this->fRoot == nullptr) {
            this->fRoot = node;
        } else {
            this->fRoot->push_front(*node);
        }

        this->fCount += 1;
    }
};
