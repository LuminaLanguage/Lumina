#include "./Parser.h"
#include "./Tokenizer.h"

std::vector<Statement*> Parser::parse(const std::string& code) {
    Tokenizer tokenizer;
    auto tokens = tokenizer.tokenize(code);
    std::vector<Statement*> statements;
    for(auto &line : tokens) {
        Statement* stmt = new Statement(line);
        statements.push_back(stmt);
    }
    return statements;
}
