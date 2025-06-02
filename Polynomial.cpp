// COS30008, Tutorial 3, 2022

#include "Polynomial.h"

#include <cmath>
#include <cstdlib>
#include <limits>

// #include <limits>

Polynomial::Polynomial() {
    this->fDegree = 0;
    for (int i = 0; i < MAX_DEGREE; i++) {
        this->fCoeffs[i] = 0;
    }
}

Polynomial Polynomial::operator*(const Polynomial &aRHS) const {
    auto res = Polynomial();

    res.fDegree = this->fDegree + aRHS.fDegree;
    for (int i = 0; i <= int(this->fDegree); i++) {
        for (int j = 0; j <= int(aRHS.fDegree); j++) {
            res.fCoeffs[i + j] += this->fCoeffs[i] * aRHS.fCoeffs[j];
        }
    }

    return res;
}

bool isclose(double a, double b) { return abs(a - b) < 1e-9; }

bool Polynomial::operator==(const Polynomial &aRHS) const {
    // we don't need to compare degrees, as long as the coefficients are equal
    // we good.
    for (int i = 0; i < MAX_DEGREE; i++) {
        // doubles we're talking about...
        if (!isclose(this->fCoeffs[i], aRHS.fCoeffs[i]))
            // if (this->fCoeffs[i] != aRHS.fCoeffs[i])
            return false;
    }
    return true;
}

std::istream &operator>>(std::istream &aIStream, Polynomial &aObject) {
    aIStream >> aObject.fDegree;
    for (int i = aObject.fDegree; i >= 0; i--)
        aIStream >> aObject.fCoeffs[i];
    return aIStream;
}

std::ostream &operator<<(std::ostream &aOStream, const Polynomial &aObject) {

    const double epsilon = std::numeric_limits<double>::epsilon();
    int minimal_mononomial_degree = 0;
    // minimal mono-nomial degree
    for (int i = 0; i <= int(aObject.fDegree); i++) {
        if (std::abs(aObject.fCoeffs[i]) > epsilon) {
            minimal_mononomial_degree = i;
            break;
        }
    }

    for (int i = aObject.fDegree; i >= 0; i--) {
        // I love floats
        if (std::abs(aObject.fCoeffs[i]) > 1e-9) {
            aOStream << aObject.fCoeffs[i] << "x^" << i;
            if (i > minimal_mononomial_degree)
                aOStream << " + ";
        }
    }
    return aOStream;
}