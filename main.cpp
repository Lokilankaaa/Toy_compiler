#include <iostream>
#include "src/symtab.h"
#include "src/ast.h"
#include "src/scanner.h"
#include "src/parser.tab.hh"

TOY_COMPILER::GlobalSymbol *globalsymtab;
TOY_COMPILER::rootProgram *root;

int main() {
    std::string filename = "../tests/test1.spl";
    std::ifstream in_file(filename);
    auto scanner = new TOY_COMPILER::Scanner(&in_file);
//    globalsymtab = new TOY_COMPILER::GlobalSymbol();
    auto parser = new TOY_COMPILER::Parser(*scanner);
    parser->parse();

    auto str = root->getNodeJson();
    std::cout << str;
    return 0;
}
