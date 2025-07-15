#include "ofstream12.h"
#include <cstddef>

ofstream12::ofstream12(const char *aFileName,
                       size_t aBufferSize){this->open(aFileName)}

ofstream12::~ofstream12() {
    delete[] this->fBuffer;
    this->fOStream.close();
}

void ofstream12::open(const char *aFileName) { this->fOStream.open(aFileName); }

void ofstream12::close() { this->fOStream.close(); }

bool ofstream12::good() const { return this->fOStream.good(); }

bool ofstream12::isOpen() const { return this->fOStream.is_open(); }