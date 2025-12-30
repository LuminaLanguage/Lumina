#pragma once
#include <string>
#include <vector>

class Tokenizer {
public:
    std::vector<std::vector<std::string>> tokenize(const std::string& code);
};
