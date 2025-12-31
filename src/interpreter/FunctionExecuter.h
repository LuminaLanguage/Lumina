#pragma once
#include "ast/FunctionNode.h"
#include "runtime/Environment.h"

class FunctionExecutor {
public:
    static void execute(FunctionNode* node, Environment& env);
};
