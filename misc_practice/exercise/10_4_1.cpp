// e1

#include <iostream>
#include <memory>

using namespace std;

class Resource {
  public:
    Resource() { cout << "constructor"; }
    ~Resource() { cout << "destructor"; }
};

int main() { unique_ptr<Resource> pointer(new Resource()); }