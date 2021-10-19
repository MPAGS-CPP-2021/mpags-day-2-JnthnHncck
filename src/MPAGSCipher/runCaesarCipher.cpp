#include <string>

#include "runCaesarCipher.hpp"

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt) {

    /*Takes each letter in in the input, and replaces it with the one that is +-key places right of
    it in the alphabet. We use + for encryption, and - for decryption.

    const std::string& inputText: This is the text to (en)/(de)crypt.
    const size_t key: The number of positions to shift a character in the alphabet.
    const bool encrypt: We encrypt if true, decrypt if false.

    returns: A string containing the (en)/(de)crypted text.
    */
    std::string outputText{""};
    int sign{1};

    if (!encrypt) {
        sign = -1;
    }

    int shift = sign*key;

    for (const auto& elem : inputText) {
        char newchar = elem + shift;
        while (newchar > 'Z') {
            newchar -= 26;
        }
        while (newchar < 'A') {
            newchar += 26;
        }
        outputText = outputText + newchar;
    }
    return outputText;
}    