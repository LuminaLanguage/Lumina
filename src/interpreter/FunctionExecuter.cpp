#include "interpreter/FunctionExecuter.h"
#include "interpreter/Executer.h"

void FunctionExecutor::execute(FunctionNode* node, Environment& env) {
    env.set(node->name, Variable()); // placeholder for function object
    Executor executor(env);
    executor.execute(node->body);
}
