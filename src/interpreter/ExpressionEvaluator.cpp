#include "ExpressionEvaluator.h"
#include <sstream>
#include <iostream>

Variable ExpressionEvaluator::evaluate(const std::string& expr, Environment& env) {
    std::istringstream iss(expr);
    std::string token;
    double result = 0;
    bool first = true;
    char op = '+';
    while(iss >> token) {
        double val = 0;
        if(env.vars.count(token)) val = env.get(token).num;
        else try { val = std::stod(token); } catch(...) { val=0; }
        if(first) { result = val; first=false; continue; }
        switch(op) {
            case '+': result += val; break;
            case '-': result -= val; break;
            case '*': result *= val; break;
            case '/': result /= val; break;
        }
        iss >> op;
    }
    return Variable(result);
}
