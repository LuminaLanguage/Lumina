#pragma once
#include "Node.h"
#include <string>
#include <vector>

class Expression : public Node {
public:
    std::vector<std::string> tokens;
    Expression(const std::vector<std::string>& t) : Node("expression"), tokens(t) {}
};
