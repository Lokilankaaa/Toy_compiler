//
// Created by xurunsen on 6/10/21.
//

#ifndef TOY_COMPILER_CODEGENERATOR_H
#define TOY_COMPILER_CODEGENERATOR_H

#include <vector>
#include <memory>

#include "ast.h"

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> TheBuilder(TheContext);

class CodeGenerator{
public:
    std::unique_ptr<llvm::Module> TheModule;

    CodeGenerator()
    {
        TheModule = std::unique_ptr<llvm::Module>(new llvm::Module("main", TheContext));
    }

    void generate_LR(rootProgram& program);
};


#endif //TOY_COMPILER_CODEGENERATOR_H
