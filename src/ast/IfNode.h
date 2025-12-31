#pragma once
#include "./Node.h"
#include <vector>
#include "ast/Statement.h"

class IfNode : public Node {
public:
    std::string condition;
    std::vector<Statement*> thenBranch;
    std::vector<Statement*> elseBranch;
    IfNode(const std::string& cond) : Node("if"), condition(cond) {}
};
