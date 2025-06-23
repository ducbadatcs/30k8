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
        this->seekstart();
    }
    this->fCipherProvider.reset();
}

iVigenereStream::~iVigenereStream() {
    // close the stream
    this->fIStream.close();
}

void iVigenereStream::open(const char *aFileName) {
    this->fIStream.open(aFileName);
}

void iVigenereStream::close() { this->fIStream.close(); }

void iVigenereStream::reset() {
    // this->fIStream.open()

    this->fCipherProvider.reset();

    this->seekstart();
}

bool iVigenereStream::good() const { return this->fIStream.good(); }

bool iVigenereStream::is_open() const { return this->fIStream.is_open(); }

bool iVigenereStream::eof() const { return this->fIStream.eof(); }

iVigenereStream &iVigenereStream::operator>>(char &aCharacter) {
    if (!this->eof()) {
        char getch = this->fIStream.get();
        if (this->fIStream.good()) {
            aCharacter = this->fCipher(this->fCipherProvider, getch);
        }
    }
    return *this;
}