#pragma once
#include "ast/Node.h"
#include <vector>
#include <string>
#include "ast/Statement.h"

class FunctionNode : public Node {
public:
    std::string name;
    std::vector<std::string> params;
    std::vector<Statement*> body;
    FunctionNode(const std::string& n) : Node("function"), name(n) {}
};
