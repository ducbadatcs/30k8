#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class Queue {
  private:
    vector<T> _elements;

  public:
    Queue() { this->_elements.clear(); }

    void enqueue(T item) { this->_elements.push_back(item); }

    T dequeue() {
        T front = this->front();
        this->_elements.erase(this->_elements.begin());
        return front;
    }

    T front() const { return this->_elements.front(); }

    bool isEmpty() const { return this->size() == 0; }

    size_t size() const { return this->_elements.size(); }
};

int main() {
    Queue<int> queue;
    for (int i = 0; i < 5; i++) {
        queue.enqueue(i);
    }
    while (!queue.isEmpty()) {
        cout << queue.dequeue() << ' ';
    }
}