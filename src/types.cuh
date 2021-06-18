//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_TYPES_CUH
#define TOY_COMPILER_TYPES_CUH

#include <string>

namespace TOY_COMPILER {

    union expValue {
        int int_value;
        double real_value;
        bool bool_value;
        char char_value;
        void *p = nullptr;
    };

    enum passBy {
        VALUE, REFER
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
        FUNCCALL,
        STMT,
        CONSTDECL,
        SIMPLEDCEL,
        ARRAYDECL,
        RECORDDECL,
        RANGEDECL,
        NAMEDECL,
        VARDECL,
        LITERAL,
        TYPEDEF,
        VARIABLE,
        MATHEXPR
    };

    enum valType {
        BOOLEAN,
        INTEGER,
        REAL,
        CHAR,
        VOID,
        COMP,
        RANGE,
        ARRAY,
        NAME,
        RECORD,
        ERROR
    };

    enum sysCON {
        TRUE, FALSE, MAXINT
    };

    union const_valueType {
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
        WRITE, WRITELN, READ
    };

    enum opType {
        LBRB,
        LPRP,
        DOT,
        MUL,
        DIV,
        UNEQUAL,
        NOT,
        AND,
        OR,
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

	enum iType {
		RANGE_AS,
		NAME_AS
	};


};     // namespace TOY_COMPILER
#endif // TOY_COMPILER_TYPES_CUH
