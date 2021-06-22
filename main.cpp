#include <iostream>
#include "src/ast.h"
#include "src/scanner.h"
#include "src/parser.tab.hh"

TOY_COMPILER::rootProgram *root;

int main() {
    std::string filename = "../tests/test3.spl";
    std::string out_file = "../vis.json";
    std::ifstream in_file(filename);
    auto scanner = new TOY_COMPILER::Scanner(&in_file);
//    globalsymtab = new TOY_COMPILER::GlobalSymbol();
    auto parser = new TOY_COMPILER::Parser(*scanner);
    parser->parse();

    auto str = root->getNodeJson();
    std::ofstream out(out_file);
    out << str;
    return 0;
}
