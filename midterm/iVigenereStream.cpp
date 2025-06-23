#include "iVigenereStream.h"
#include <cctype>
#include <cstdio>

iVigenereStream::iVigenereStream(Cipher aCipher, const std::string &aKeyword,
                                 const char *aFileName)
    : fCipherProvider(aKeyword) {

    this->fCipher = aCipher;
    if (aFileName != nullptr) {
        // open the stream, well I'd cba this for later
        this->open(aFileName);
    }
}

iVigenereStream::~iVigenereStream() {
    // close the stream
    this->fIStream.close();
}

void iVigenereStream::open(const char *aFileName) {
    this->fIStream.open(aFileName);
}

void iVigenereStream::close() { this->fIStream.close(); }

void iVigenereStream::reset() { this->seekstart(); }

bool iVigenereStream::good() const { return this->fIStream.good(); }

bool iVigenereStream::is_open() const { return this->fIStream.is_open(); }

bool iVigenereStream::eof() const { return this->fIStream.eof(); }

iVigenereStream &iVigenereStream::operator>>(char &aCharacter) {

    char getch = this->fIStream.get();
    // Apply cipher only if character is alphabetic
    aCharacter = this->fCipher(this->fCipherProvider, getch);

    return *this;
}