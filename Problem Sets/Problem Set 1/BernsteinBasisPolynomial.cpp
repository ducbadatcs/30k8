#include <cstdarg>
#define __USE_MATH_DEFINES
#include "BernsteinBasisPolynomial.h"
#include "Combination.h"
#include <cmath>
#include <iostream>

BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV,
                                                   unsigned int aN) {
    this->fFactor = Combination(aN, aV);
}

// Do you only need to output the polynomial's value at a certain point?
// Because that's exactly what the problem asks. You're not required to
// output the polynomial.

double BernsteinBasisPolynomial::operator()(double aX) const {
    size_t v = this->fFactor.getK(), n = this->fFactor.getN();

    // avoid numbers getting too small by putting a big number inbetween
    return pow(aX, v) * this->fFactor() * pow(1 - aX, n - v);
}