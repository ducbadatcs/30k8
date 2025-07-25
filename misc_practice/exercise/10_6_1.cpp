#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T> class Stack {
  private:
    vector<T> _elements;

  public:
    Stack() { this->_elements.clear(); }

    void push(T item) { this->_elements.push_back(item); }

    T pop() {
        if (this->isEmpty()) {
            throw out_of_range("Can't pop element in empty stack!");
        }
        T top = this->top();
        this->_elements.pop_back();
        return top;
    }

    T top() const { return this->_elements.back(); }

    bool isEmpty() const { return this->size() == 0; }

    size_t size() const { return this->_elements.size(); }
};

int main() {
    Stack<int> st;
    for (int i = 0; i < 5; i++) {
        st.push(i);
    }

    while (!st.isEmpty()) {
        cout << st.pop() << ' ';
    }
}