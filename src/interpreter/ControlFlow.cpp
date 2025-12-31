#include "./ControlFlow.h"
#include "interpreter/Executor.h"
#include "interpreter/ExpressionEvaluator.h"

void ControlFlow::executeIf(IfNode* node, Environment& env) {
    Variable cond = ExpressionEvaluator::evaluate(node->condition, env);
    Executor executor(env);
    if(cond.num != 0) executor.execute(node->thenBranch);
    else executor.execute(node->elseBranch);
}

void ControlFlow::executeFor(ForNode* node, Environment& env) {
    double start = std::stod(node->start);
    double end = std::stod(node->end);
    Executor executor(env);
    for(double i=start;i<end;i++) {
        env.set(node->varName, Variable(i));
        executor.execute(node->body);
    }
}

void ControlFlow::executeWhile(WhileNode* node, Environment& env) {
    Executor executor(env);
    while(ExpressionEvaluator::evaluate(node->condition, env).num != 0) {
        executor.execute(node->body);
    }
}
