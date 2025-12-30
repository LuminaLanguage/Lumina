#pragma once
#include "Node.h"
#include <vector>
#include <string>

class Statement : public Node {
public:
    std::vector<std::string> tokens;
    std::string value;
    Statement(const std::vector<std::string>& t) : Node("statement"), tokens(t) {
        if(!tokens.empty()) value = tokens[0];
    }
};
