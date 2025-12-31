#pragma once
#include "ast/Statement.h"
#include "runtime/Environment.h"

class StatementExecutor {
public:
    static void execute(Statement* stmt, Environment& env);
};
