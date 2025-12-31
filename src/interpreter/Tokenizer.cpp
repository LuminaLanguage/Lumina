#include "./Tokenizer.h"
#include <sstream>

std::vector<std::vector<std::string>> Tokenizer::tokenize(const std::string& code) {
    std::vector<std::vector<std::string>> result;
    std::istringstream iss(code);
    std::string line;
    while(std::getline(iss, line)) {
        std::istringstream lss(line);
        std::vector<std::string> tokens;
        std::string word;
        while(lss >> word) tokens.push_back(word);
        result.push_back(tokens);
    }
    return result;
}
