#include <iostream>
#include "src/symtab.h"

TOY_COMPILER::GlobalSymbol *globalsymtab;

int main() {
    std::cout << "Hello, World!" << std::endl;
    globalsymtab = new TOY_COMPILER::GlobalSymbol();
    return 0;
}
