#include "interpreter/Executor.h"
#include "runtime/Variable.h"
#include <iostream>

void Executor::execute(const std::vector<Statement*>& stmts) {
    for(auto stmt : stmts) executeStatement(stmt);
}

void Executor::executeStatement(Statement* stmt) {
    if(stmt->tokens.empty()) return;
    if(stmt->tokens[0] == "var" || stmt->tokens[0] == "let") {
        std::string name = stmt->tokens[1];
        std::string val = stmt->tokens.size() > 3 ? stmt->tokens[3] : "";
        env.set(name, Variable(val));
    } else if(stmt->tokens[0] == "print") {
        for(size_t i=1;i<stmt->tokens.size();i++) {
            std::string t = stmt->tokens[i];
            if(env.vars.count(t)) std::cout << env.get(t).str << " ";
            else std::cout << t << " ";
        }
        std::cout << std::endl;
    }
}
