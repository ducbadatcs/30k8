
#include "Polygon.h"

using namespace std;

inline float det(float a, float b, float c, float d) {
    // determinant of [a b; c d] in MATLAB notation
    return a * d - b * c;
}

float Polygon::getSignedArea() const {
    float fArea = 0;
    int n = this->fNumberOfVertices;
    for (int i = 0; i < n - 1; i++) {
        fArea += det(this->getVertex(i).getX(), this->getVertex(i + 1).getX(),
                     this->getVertex(i).getY(), this->getVertex(i + 1).getY());
    }
    fArea += det(this->getVertex(n - 1).getX(), this->getVertex(0).getX(),
                 this->getVertex(n - 1).getY(), this->getVertex(0).getY());
    return fArea / 2.0;
}
