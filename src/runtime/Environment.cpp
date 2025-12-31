#include "./Environment.h"

void Environment::set(const std::string& name, const Variable& val) {
    vars[name] = val;
}

Variable Environment::get(const std::string& name) {
    if(vars.count(name)) return vars[name];
    return Variable();
}
