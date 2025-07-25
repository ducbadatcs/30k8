#include <iostream>
#include <memory>

using namespace std;

class Shape {
  public:
    virtual unique_ptr<Shape> clone() const = 0;
};

class Circle : Shape {
  private:
    double radius;

  public:
    unique_ptr<Shape> clone() const override {
        return make_unique<Circle>(*this);
    }
};