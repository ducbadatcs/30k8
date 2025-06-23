#include "KeyProvider.h"
#include <cctype>
#include <cstdlib>
#include <string>

KeyProvider::KeyProvider(const std::string &aKeyword) {
    // I love redundancy
    // because I genuinely don't get what's the difference
    // if initialize does pretty much the same thing anyway
    this->initialize(aKeyword);
}

KeyProvider::~KeyProvider() { delete[] this->fKeyword; }

void KeyProvider::initialize(const std::string &aKeyword) {
    // wait we are basically doing the same thing again

    // "Relations" -> "RELATIONS", so everything here has to be...
    // explicitly in uppercase in the first place?
    this->fSize = aKeyword.size();

    this->fKeyword = new char[this->fSize];
    for (size_t i = 0; i < this->fSize; i++) {
        //  a little test won't hurt
        if (std::isalpha(aKeyword[i])) {
            this->fKeyword[i] = toupper(aKeyword[i]);
        }
    }
    this->fIndex = 0;
}

char KeyProvider::operator*() const {
    // avoid overflow?
    return this->fKeyword[this->fIndex];
}

KeyProvider &KeyProvider::operator<<(char aKeyCharacter) {
    // replace current char
    this->fKeyword[this->fIndex % this->fSize] = toupper(aKeyCharacter);

    // advance to next

    // is this what I think it is
    this->fIndex = (this->fIndex + 1) % this->fSize;
    // this->fSize += 1;
    return (*this);
}