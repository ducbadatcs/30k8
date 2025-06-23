// #include "KeyProvider.cpp"
// #include "KeyProvider.h"
#include "Vigenere.h"
#include <cctype>
#include <iostream>
#include <string>
#include <type_traits>

// this syntax makes no sense. really. It's for derived classes.
// why do I have to do it like this is beyond me. Vigenere does NOT derive
// from fKeywordProvider.

// also I discovered this multiple member initializer syntax by accident
// and I have a question
// WHYYYYYYYY???????????
Vigenere::Vigenere(const std::string &aKeyword)
    : fKeyword(aKeyword), fKeywordProvider(aKeyword) {

    // this->fKeyword = const_cast<std::string>(*aKeyword);

    // this->fKeyword = static_cast<const std::string>(aKeyword);

    this->initializeTable();

    this->reset();
}

std::string Vigenere::getCurrentKeyword() {
    std::string result = "";
    auto p = this->fKeywordProvider;
    for (int i = 0; i < this->fKeyword.size(); i++) {
        char c = *p;
        // std::cout << c;
        result.push_back(c);
        p << c;
    }
    // need to reset
    this->reset();
    return result;
}

void Vigenere::reset() {
    // at least this one is ok I guess
    this->fKeywordProvider.initialize(this->fKeyword);
}

// ok I'm gonna throw the algo here.
// basically, by the table, if we do a map
// we can map A-Z to 0-25 range
// and the encoding letter for letters $a, b$ is (a + b + 1) mod 26
// accordingly.
// in other words, if we encode a char $a$ with key $b$,
// we return (a + b + 1) % 26.
// and if we decode a char $c$ with key $b$, we return (c - b - 1) % 26

char Vigenere::encode(char aCharacter) {
    // to encode a char
    // uh

    if (!std::isalpha(aCharacter)) {
        return aCharacter;
    }

    int D = std::toupper(aCharacter) - 'A', K = *this->fKeywordProvider - 'A';
    this->fKeywordProvider << static_cast<char>('A' + K);
    // std::cout << char(D) << ' ' << char(K) << ' ';
    int S = (D + K + 1) % 26;
    // std::cout << S << std::endl;
    // std::cout << (char) D << ' ' << (char) K << '\n';
    return (std::isupper(aCharacter) ? 'A' : 'a') + S;
}

char Vigenere::decode(char aCharacter) {

    if (!std::isalpha(aCharacter)) {
        return aCharacter;
    }

    int S = std::toupper(aCharacter) - 'A', K = *this->fKeywordProvider - 'A';

    this->fKeywordProvider << static_cast<char>('A' + K);
    int D = ((S - K - 1) + 26) % 26;
    return (std::isupper(aCharacter) ? 'A' : 'a') + (D % 26);
}