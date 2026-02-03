#include "Tokenizer.h"
#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string word;

    for (unsigned char c : text) {
        if (std::isalpha(c)) {
            word.push_back(std::tolower(c));
        } else {
            if (!word.empty()) {
                tokens.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) tokens.push_back(word);
    return tokens;
}
