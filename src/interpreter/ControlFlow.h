#pragma once
#include "../ast/IfNode.h"
#include "../ast/ForNode.h"
#include "../ast/WhileNode.h"
#include "../runtime/Environment.h"

class ControlFlow {
public:
    static void executeIf(IfNode* node, Environment& env);
    static void executeFor(ForNode* node, Environment& env);
    static void executeWhile(WhileNode* node, Environment& env);
};
