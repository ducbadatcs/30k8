#include "VigenereForwardIterator.h"
#include "Vigenere.h"
#include "iVigenereStream.h"
#include <cstdio>
#include <iostream>

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream &aIStream)
    : fIStream(aIStream) {
    this->fIStream >> this->fCurrentChar; // Reads first character
    this->fEOF = false;
    if (this->fIStream.eof() ||
        !(this->fIStream >>
          this->fCurrentChar)) { // PROBLEM: Reads SECOND character
        this->fEOF = true;
    }
}

char VigenereForwardIterator::operator*() const {
    // std::cout << this->fCurrentChar;
    return !this->fEOF ? this->fCurrentChar : EOF;
}

VigenereForwardIterator &VigenereForwardIterator::operator++() {
    if (!(fIStream >> fCurrentChar)) {
        fEOF = true;
        return *this;
    }
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int) {
    VigenereForwardIterator temp = *this;
    ++(*this);
    return temp;
}

bool VigenereForwardIterator::operator==(
    const VigenereForwardIterator &aOther) const {
    if (this->fEOF && aOther.fEOF)
        return true;
    else if (this->fEOF != aOther.fEOF)
        return false;
    else
        return this->fCurrentChar == aOther.fCurrentChar;
}

bool VigenereForwardIterator::operator!=(
    const VigenereForwardIterator &aOther) const {
    return !this->operator==(aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const {
    return VigenereForwardIterator(this->fIStream);
}

VigenereForwardIterator VigenereForwardIterator::end() const {
    // Create an end sentinel iterator
    VigenereForwardIterator endIterator(this->fIStream);
    endIterator.fEOF = true; // Mark as end iterator
    return endIterator;
}