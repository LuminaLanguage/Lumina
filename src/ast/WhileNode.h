#pragma once
#include "./Node.h"
#include <vector>
#include "ast/Statement.h"
#include <string>

class WhileNode : public Node {
public:
    std::string condition;
    std::vector<Statement*> body;
    WhileNode(const std::string& cond) : Node("while"), condition(cond) {}
};
