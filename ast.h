//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_AST_H
#define TOY_COMPILER_AST_H

#include "types.cuh"
#include <iostream>
#include <vector>

namespace TOY_COMPILER {
    class abstracAST {
    public:
        virtual void print(std::fstream &fout) = 0;

        abstracAST *father = nullptr;
        TOY_COMPILER::ASTType n_type;
    };

    class abstractStmt : public abstracAST {
    public:
        abstractStmt() {
            n_type = TOY_COMPILER::STMT;
        }
    };

    class abstractExpr : public abstracAST {
    public:
        abstractExpr() {
            n_type = TOY_COMPILER::EXPRESSION;
        }

    protected:
        TOY_COMPILER::expValue m_value;
    };

    class mathExpr : public abstractExpr {
    public:
        // +, -, *, /, , %, &, |, !, -(num), >, >=, <, <=, <>
        void print(std::fstream &fout) override;

        mathExpr(TOY_COMPILER::opType t, mathExpr *l, mathExpr *r) : type{t}, left{l}, right{r} {}

    protected:
        TOY_COMPILER::opType type;
        mathExpr *left;
        mathExpr *right;
    };

    class stmtList : public abstracAST {
    public:
        stmtList() {
            n_type = TOY_COMPILER::STMTLIST;
        }

        bool addStmt(abstractStmt *stmt);

        void print(std::fstream &fout) override;

    protected:
        std::vector<abstractStmt *> m_stmtList;

    };

    class ifStmt : public abstractStmt {
    public:
        ifStmt(mathExpr *cond, abstractStmt *execStmt, abstractStmt *elseStmt) : cond{cond}, execStmt{execStmt},
                                                                                 elseStmt{elseStmt} {
            n_type = TOY_COMPILER::IFSTMT;
        }

    protected:
        // if cond then execStmt [else elseStmt]
        mathExpr *cond;
        abstractStmt *execStmt;
        abstractStmt *elseStmt;

        void print(std::fstream &fout) override;
    };

    class repeatStmt : public abstractStmt {
    public:
        repeatStmt(mathExpr *cond, stmtList *stmtlist) : cond{cond}, stmtlist{stmtlist} {
            n_type = TOY_COMPILER::REPEATSTMT;
        }

        void print(std::fstream &fout) override;

    protected:
        //repeat stmtlists until cond
        stmtList *stmtlist;
        mathExpr *cond;
    };

    class whileStmt : public abstractStmt {
    public:
        whileStmt(mathExpr *cond, abstractStmt *stmt) : cond{cond}, stmt{stmt} {
            n_type = TOY_COMPILER::WHILESTMT;
        }

        void print(std::fstream &fout) override;

    protected:
        // while cond do stmt
        abstractStmt *stmt;
        mathExpr *cond;
    };

    class forStmt : public abstractStmt {
    public:
        forStmt(mathExpr *from, mathExpr *to, bool direction, abstractStmt *stmt) : from{from}, to{to},
                                                                                    direction{direction}, stmt{stmt} {
            n_type = TOY_COMPILER::FORSTMT;
        }

        void print(std::fstream &fout) override;

    protected:
        //FOR  ID  ASSIGN  from  direction  to  DO stmt
        mathExpr *from;
        mathExpr *to;
        bool direction;
        abstractStmt *stmt;
    };

    class constNode : public abstracAST {
        //TODO: add const node
    public:
        constNode(TOY_COMPILER::expValue v) : m_value{v} {}

        TOY_COMPILER::expValue get_value() const { return m_value; }

    protected:
        TOY_COMPILER::expValue m_value;
    };

    class caseExpr {
    public:
        // if case_
        constNode *case_;
        mathExpr *expr;
    };

    class caseStmt : public abstractStmt {
    public:
        caseStmt(mathExpr *cond) : case_cond{cond} {
            n_type = TOY_COMPILER::CASESTMT;
        }

        void print(std::fstream &fout) override;

        void addCase(caseExpr *case_expr) const;

    protected:
        // CASE expression OF case_expr_list  END
        mathExpr *case_cond;
        std::vector<caseExpr *> case_expr_list;
    };

    class gotoStmt : public abstractStmt {
    public:
        gotoStmt(int l) : label{l} {
            n_type = TOY_COMPILER::GOTOSTMT;
        }

        void print(std::fstream &fout) override;

    protected:
        int label;
    };

    class assignStmt : public abstractStmt {
//        ID  ASSIGN  expression
//        | ID LB expression RB ASSIGN expression
//        | ID  DOT  ID  ASSIGN  expression


    public:
        assignStmt(abstractExpr *l, abstractExpr *r) : lhs{l}, rhs{r} {
            n_type = TOY_COMPILER::ASSIGNSTMT;
        }

    protected:
        abstractExpr *lhs;
        abstractExpr *rhs;
    };

    class functionNode : public abstracAST {
    public:
        functionNode(std::string name, std::vector<abstractExpr *> *agrs, stmtList *body, bool isProc, bool isSys)
                : func_symbol{name}, argList{agrs}, body{body} {
            isProc = isProc;
            isSys = isSys;
            n_type = TOY_COMPILER::FUNCTION;
        }

    protected:
        TOY_COMPILER::Symbol func_symbol;
        bool isProc;
        bool isSys;
        std::vector<abstractExpr *> *argList;
        stmtList *body;
    };


}

#endif //TOY_COMPILER_AST_H
