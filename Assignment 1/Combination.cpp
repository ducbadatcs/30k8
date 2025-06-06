
#include "Combination.h"
#include <cstddef>

using namespace std;

Combination::Combination(size_t aN, size_t aK) {
    this->fK = aK;
    this->fN = aN;
}

size_t Combination::getK() const { return this->fK; }
size_t Combination::getN() const { return this->fN; }

unsigned long long Combination::operator()() const {
    unsigned long long result = 1;
    for (size_t i = 1; i <= int(this->fK); i++) {
        result *= (this->fN - (i - 1));
        result /= i;
    }
    return result;
}