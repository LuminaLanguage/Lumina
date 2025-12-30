#pragma once
#include <string>
#include <vector>
#include <map>

class Variable {
public:
    std::string str;
    double num;
    bool isString = true;
    std::vector<Variable> arr;
    std::map<std::string, Variable> obj;
    Variable() { str=""; num=0; isString=true; }
    Variable(std::string s) { str=s; num=0; isString=true; }
    Variable(double n) { str=""; num=n; isString=false; }
};
