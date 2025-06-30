#include "ListPS3.h"
#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"
#include <cstddef>

template <typename T> List<T>::List() {
    // idk what to write here
    this->fRoot = new Node();
    this->fCount = 0;
}

template <typename T> bool List<T>::empty() const {
    return this->fCount == 0 || this->fRoot == nullptr;
}

template <typename T> size_t List<T>::size() const { return this->fCount; }

template <typename T> void List<T>::push_front(const T &aElement) {
    auto node = DoublyLinkedList<T>(aElement);
    this->fRoot->push_front(node);
    this->fCount += 1;
}

template <typename T> DoublyLinkedListIterator<T> List<T>::begin() const {
    return DoublyLinkedListIterator<T>(this->fRoot).begin();
}

template <typename T> DoublyLinkedListIterator<T> List<T>::end() const {
    return DoublyLinkedListIterator<T>(this->fRoot).end();
}

template <typename T> DoublyLinkedListIterator<T> List<T>::rbegin() const {
    return DoublyLinkedListIterator<T>(this->fRoot).rbegin();
}

template <typename T> DoublyLinkedListIterator<T> List<T>::rend() const {
    return DoublyLinkedListIterator<T>(this->fRoot).rend();
}
