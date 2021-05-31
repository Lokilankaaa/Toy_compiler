//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_SYMTAB_H
#define TOY_COMPILER_SYMTAB_H

#include <string>
#include "ast.h"
#include "types.cuh"
#include <map>

namespace TOY_COMPILER {
    class Symtab {
    protected:
        std::map<std::string, abstracAST *> symtab;
    public:
        Symtab();

        void addMap(std::string name, abstracAST * ast);
    };
}


#endif //TOY_COMPILER_SYMTAB_H
