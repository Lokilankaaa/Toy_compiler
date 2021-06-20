#include <iostream>
#include "src/ast.h"
#include "src/scanner.h"
#include "src/parser.tab.hh"
#include "src/IR.h"

TOY_COMPILER::rootProgram *root;
std::map<int, TOY_COMPILER::abstractStmt*>  Label;
int main() {
    std::string filename = "../tests/test3.spl";
    std::string out_file = "../vis.json";
    std::ifstream in_file(filename);
    auto scanner = new TOY_COMPILER::Scanner(&in_file);
    auto parser = new TOY_COMPILER::Parser(*scanner);
    parser->parse();

    auto str = root->getNodeJson();
    std::ofstream out(out_file);
    out << str;

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    TOY_COMPILER::IR generator;
    generator.generate(root);

    return 0;
}
