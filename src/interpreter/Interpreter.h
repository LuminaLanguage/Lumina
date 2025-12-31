#pragma once
#include <string>
#include "interpreter/Parser.h"
#include "interpreter/Executer.h"
#include "runtime/Environment.h"

class Interpreter {
public:
    Environment global;
    void run(const std::string& code);
};
