#pragma once
#include "./Expression.h"
#include <string>

class Literal : public Expression {
public:
    std::string strValue;
    double numValue;
    bool isString = true;
    Literal(const std::string& val) : Expression({val}), strValue(val), numValue(0), isString(true) {}
    Literal(double val) : Expression({}), strValue(""), numValue(val), isString(false) {}
};
