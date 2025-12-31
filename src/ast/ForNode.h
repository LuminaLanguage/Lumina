#pragma once
#include "ast/Node.h"
#include <vector>
#include "ast/Statement.h"
#include <string>

class ForNode : public Node {
public:
    std::string varName;
    std::string start;
    std::string end;
    std::vector<Statement*> body;
    ForNode(const std::string& v, const std::string& s, const std::string& e)
        : Node("for"), varName(v), start(s), end(e) {}
};
