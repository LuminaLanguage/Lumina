#pragma once
#include <string>
#include <vector>
#include "../ast/Statement.h"

class Parser {
public:
    std::vector<Statement*> parse(const std::string& code);
};
