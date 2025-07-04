#include "SortableIntVector.h"
#include "IntVector.h"
#include <cstddef>

SortableIntVector::SortableIntVector(const int aArrayOfIntegers[],
                                     size_t aNumberOfElements)
    : IntVector(aArrayOfIntegers, aNumberOfElements) {}

void SortableIntVector::sort(Comparable aOrderFunction) {
    size_t n = this->size();
    for (size_t i = 0; i <= n - 1; i++) {
        for (size_t j = n - 1; j >= i + 1; j--) {

            // turns out you can just do this. If you flip it, it will sort in
            // reverse and the reason is that we are following the sort lambda
            // in Main. so in essence, you could define aOrderFunction as the
            // lambda to check a > b, but that would go against the definition
            // of our Comparable here, so I won't do that.

            if (aOrderFunction(this->get(j), this->get(j - 1))) {
                // swap(a[j], a[j - 1])
                this->swap(j, j - 1);
            }
        }
    }
}