
#include "Polynomial.h"
#include <cmath>

using namespace std;

double Polynomial::operator()(double aX) const {
    double result = 0;
    for (int i = 0; i <= int(this->fDegree); i++) {
        result += this->fCoeffs[i] * pow(aX, i);
    }
    return result;
}

Polynomial Polynomial::getDerivative() const {
    Polynomial derivative = Polynomial();
    for (int i = 1; i <= this->fDegree; i++) {
        derivative.fCoeffs[i - 1] = this->fCoeffs[i] * i;
    }
    derivative.fDegree = this->fDegree - 1;
    return derivative;
}

Polynomial Polynomial::getIndefiniteIntegral() const {
    Polynomial integral = Polynomial();
    for (int i = 0; i <= this->fDegree; i++) {
        integral.fCoeffs[i + 1] = this->fCoeffs[i] / (i + 1);
    }
    integral.fDegree = this->fDegree + 1;
    return integral;
}

double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const {
    Polynomial integral = this->getIndefiniteIntegral();
    return integral(aXHigh) - integral(aXLow);
}