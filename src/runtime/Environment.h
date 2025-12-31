#pragma once
#include <map>
#include <string>
#include "runtime/Variable.h"

class Environment {
public:
    std::map<std::string, Variable> vars;
    void set(const std::string& name, const Variable& val);
    Variable get(const std::string& name);
};
