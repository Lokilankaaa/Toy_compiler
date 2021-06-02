//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_TYPES_CUH
#define TOY_COMPILER_TYPES_CUH

#include <string>
#include "ast.h"

namespace TOY_COMPILER {
class Symbol {
    protected:
        std::string name;
        bool isfunc;

    public:
        Symbol(std::string &name, bool isfunc) : name{name}, isfunc{isfunc} {

        }

        std::string get_name() { return name; }
    };

    union expValue {
        int int_value;
        double real_value;
        bool bool_value;
        char char_value;
        void * p = nullptr;
    };

    enum passBy {
        VALUE,
        REFER
    };

    enum ASTType {
        PROGRAM,
        FUNCTION,
        STMTLIST,
        IFSTMT,
        FORSTMT,
        WHILESTMT,
        CASESTMT,
        GOTOSTMT,
        REPEATSTMT,
        ASSIGNSTMT,
        EXPRESSION,
        STMT,
        CONSTDECL,
        SIMPLEDCEL,
        ARRAYDECL,
        RECORDDECL,
        RANGEDECL,
        NAMEDECL,
        VARDECL,
    };

    enum valType {
        BOOLEAN,
        INTEGER,
        REAL,
        CHAR
    };

    enum sysCON {
        TRUE,
        FALSE,
        MAXINT
    };

    union const_valueTye{
        valType d_type;
        sysCON sys_type;
    };

    enum sysFUNC {
        ABS,
        CHR,
        ODD,
        ORD,
        PRED,
        SQR,
        SUCC,
        SQRT,
    };

    enum sysPROC {
        WRITE,
        WRITELN,
        READ
    };

    enum opType {
        LP,
        RP,
        LB,
        RB,
        DOT,
        COMMA,
        COLON,
        MUL,
        DIV,
        UNEQUAL,
        NOT,
        PLUS,
        MINUS,
        GE,
        GT,
        LE,
        LT,
        EQUAL,
        ASSIGN,
        MOD,
        DOTDOT,
        SEMI
    };

};
#endif //TOY_COMPILER_TYPES_CUH
