#pragma once
#include "ast/Statement.h"
#include "runtime/Environment.h"
#include <vector>

class Executor {
    Environment& env;
public:
    Executor(Environment& e) : env(e) {}
    void execute(const std::vector<Statement*>& stmts);
    void executeStatement(Statement* stmt);
};
