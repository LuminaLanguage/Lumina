#pragma once
#include <vector>
#include <string>
#include "../ast/Statement.h"

class Function {
public:
    std::string name;
    std::vector<std::string> params;
    std::vector<Statement*> body;
    Function() {}
    Function(const std::string& n) : name(n) {}
};
