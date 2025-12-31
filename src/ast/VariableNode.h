#pragma once
#include "./Node.h"
#include <string>

class VariableNode : public Node {
public:
    std::string name;
    VariableNode(const std::string& n) : Node("variable"), name(n) {}
};
