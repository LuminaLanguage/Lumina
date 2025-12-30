#pragma once
#include <string>

class Node {
public:
    std::string type;
    Node(const std::string& t) : type(t) {}
    virtual ~Node() {}
};
