#pragma once
#include <string>
#include "../runtime/Environment.h"
#include "../runtime/Variable.h"

class ExpressionEvaluator {
public:
    static Variable evaluate(const std::string& expr, Environment& env);
};
