#include <string>

#include "TransformChar.hpp" 

std::string transformChar(const char in_char)
{
    /* Converts a given character into upper case if it is a letter, and a string naming the number if it is a number.

    const char in_char: The character to be converted.

    return: The string or character described in the first line.
    */
   
    if (std::isalpha(in_char)) {
            char x = std::toupper(in_char);
            std::string s(1, x);
            return(s);
        }

        // Transliterate digits to English words
        switch (in_char) {
            case '0':
                return("ZERO");
                break;
            case '1':
                return("ONE");
                break;
            case '2':
                return("TWO");
                break;
            case '3':
                return("THREE");
                break;
            case '4':
                return("FOUR");
                break;
            case '5':
                return("FIVE");
                break;
            case '6':
                return("SIX");
                break;
            case '7':
                return("SEVEN");
                break;
            case '8':
                return("EIGHT");
                break;
            case '9':
                return("NINE");
                break;
        }
    return("");
}