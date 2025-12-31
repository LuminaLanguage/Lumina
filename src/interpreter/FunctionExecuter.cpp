#include "interpreter/FunctionExecutor.h"
#include "interpreter/Executor.h"

void FunctionExecutor::execute(FunctionNode* node, Environment& env) {
    env.set(node->name, Variable()); // placeholder for function object
    Executor executor(env);
    executor.execute(node->body);
}
