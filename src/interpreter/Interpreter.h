#pragma once
#include <string>
#include "Parser.h"
#include "Executor.h"
#include "runtime/Environment.h"

class Interpreter {
public:
    Environment global;
    void run(const std::string& code);
};
