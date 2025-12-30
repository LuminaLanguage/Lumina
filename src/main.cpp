#include "interpreter/Interpreter.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    if(argc < 2) return 1;
    std::ifstream file(argv[1]);
    if(!file.is_open()) return 1;
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    Interpreter interp;
    interp.run(code);
    return 0;
}
