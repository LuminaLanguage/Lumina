#include "Interpreter.h"

void Interpreter::run(const std::string& code) {
    Parser parser;
    auto statements = parser.parse(code);
    Executor executor(global);
    executor.execute(statements);
}
