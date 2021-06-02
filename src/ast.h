//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_AST_H
#define TOY_COMPILER_AST_H

#include "types.cuh"
#include <iostream>
#include <utility>
#include <vector>

#define GETTER(var, method_name) decltype(var) method_name() const;

namespace TOY_COMPILER {
    class abstractAST {
    public:
        virtual void print(std::fstream &fout) {

        }

        abstractAST *father = nullptr;
        TOY_COMPILER::ASTType n_type;
    };

    class abstractStmt : public abstractAST {
    public:
        abstractStmt() {
            n_type = TOY_COMPILER::STMT;
        }
    };

    class abstractExpr : public abstractStmt {
    public:
        abstractExpr() {
            n_type = TOY_COMPILER::EXPRESSION;
            m_value.p = nullptr;
        }

    protected:
        TOY_COMPILER::expValue m_value;
        TOY_COMPILER::valType res_type;
    };

    class abstractTypeDeclNode : public abstractAST {
    public:
        abstractTypeDeclNode() {
            n_type = TOY_COMPILER::SIMPLEDCEL;
        }
    };

    // mark class
    class abstractSimpleDecl {
    };

    class constNode {
        // NAME  EQUAL  const_value
    public:
        constNode(std::string id, TOY_COMPILER::const_valueTye t) {
            id = id;
            const_type = t;
        }

        GETTER(id, getId)

        GETTER(const_type, getType)

    protected:
        std::string id;
        TOY_COMPILER::const_valueType const_type;
    };

    class constDecl : public abstractExpr {
        // CONST const_expr_list  NAME  EQUAL  const_value  SEMI
    public:
        constDecl() {
            n_type = TOY_COMPILER::CONSTDECL;
        }

        void print(std::fstream &fout) override;

        void addConstDecl(std::string id, TOY_COMPILER::const_valueTye t);

        GETTER(constdecls, getDecls)

    protected:
        std::vector<constNode *> constdecls;
    };

    class simpleDecl : public abstractTypeDeclNode, public abstractSimpleDecl {
    public:
        // simple_type_decl:   sys_type
        simpleDecl(std::string id, TOY_COMPILER::valType t) : id{std::move(id)}, val_type{t} {

        }

        GETTER(id, getId)

    protected:
        TOY_COMPILER::valType val_type;
        std::string id;
    };

    class rangeDecl : public abstractTypeDeclNode, public abstractSimpleDecl {
    public:
        // simple_type_decl:   NAME  DOTDOT  NAME
        rangeDecl(std::string id, std::string l, std::string r) : id{std::move(id)}, id_l{std::move(l)},
                                                                  id_r{std::move(r)} {
            n_type = TOY_COMPILER::RANGEDECL;
        }


        //simple_type_decl:  const_value  DOTDOT  const_value
        //                |  MINUS  const_value  DOTDOT  const_value
        //                |  MINUS  const_value  DOTDOT  MINUS  const_value
        rangeDecl(std::string id, bool m_l, const_valueType c_l, bool m_r, const_valueType c_r) : id{id}, minus_l{m_l},
                                                                                                  con_l{c_l},
                                                                                                  minus_r{m_r},
                                                                                                  con_r{c_r} {

        }

        GETTER(id, getId)

        GETTER(con_l, getLeftRange)

        GETTER(con_r, getRightRange)

        GETTER(minus_l, getLeftSign)

        GETTER(minus_r, getRightSign)

    protected:
        std::string id;
        TOY_COMPILER::const_valueType *con_l, *con_r;
        bool minus_l, minus_r;
    };

    class namesDecl : public abstractTypeDeclNode, public abstractSimpleDecl {
    public:
        //simple_type_decl ：  NAME  |  LP  name_list  RP  (can judge whether NAME or name_list by the length of vector)
        namesDecl(std::string id, std::vector<std::string> names) : id{std::move(id)}, names{std::move(names)} {
            n_type = TOY_COMPILER::NAMEDECL;
        }

        void addName(std::string name);

        GETTER(id, getId);

        GETTER(names, getNames)

    protected:
        std::string id;
        std::vector<std::string> names;
    };

    class arrayDecl : public abstractTypeDeclNode {
    public:
        //ARRAY  LB  simple_type_decl  RB  OF  type_decl
        arrayDecl(std::string id, abstractSimpleDecl *sim_types,
                  abstractTypeDeclNode *type_decl) : id{std::move(id)}, sim_type{sim_types},
                                                     type_decl{type_decl} {
            n_type = TOY_COMPILER::ARRAYDECL;
        }

        GETTER(id, getId);

        GETTER(sim_type, getSimpleType)

        GETTER(type_decl, getTypeDecl)

    protected:
        std::string id;
        abstractSimpleDecl *sim_type;
        abstractTypeDeclNode *type_decl;
    };

    class record {
    public:
        record(std::vector<std::string> ns, std::vector<abstractTypeDeclNode *> ts) {
            record = std::make_pair(ns, ts);
        }

        record &getDetail() const;

    protected:
        std::pair<std::vector<std::string>, std::vector<abstractTypeDeclNode *> > record
    };

    class recordDecl : public abstractTypeDeclNode {
    public:
        recordDecl() {
            n_type = TOY_COMPILER::RECORDDECL;
        }

        void addRecord(record r);

        decltype(records) &getRecords() const;

    protected:
        std::vector<record *> records
    };

    class varNode {
    public:
        varNode(std::string id, abstractTypeDeclNode *inferType) : id{std::move(id)}, varType{inferType} {

        }

        decltype()
    protected:
        std::string id;
        abstractTypeDeclNode *varType;
    };

    class varDecl : public abstractTypeDeclNode {
    public:
        varDecl() {
            n_type = TOY_COMPILER::VARDECL;
        }

        void addDecl(varNode *);

        decltype(decls) &getDecls() const;

    protected:
        std::vector<varNode *> decls;
    };

    class variableNode : abstractExpr {

    };

    class mathExpr : public abstractExpr {
    public:
        // +, -, *, /, , %, &, |, !, -(num), >, >=, <, <=, <>
        void print(std::fstream &fout) override;

        mathExpr(TOY_COMPILER::opType t, mathExpr *l, mathExpr *r) : type{t}, left{l}, right{r} {}

        GETTER(left, getLeftChild)

        GETTER(right, getRightChild)

        GETTER(type, getOp)

    protected:
        TOY_COMPILER::opType type;
        abstractExpr *left;
        abstractExpr *right;
    };

    class stmtList : public abstractAST {
    public:
        stmtList() {
            n_type = TOY_COMPILER::STMTLIST;
        }

        void addStmt(abstractStmt *stmt);

        decltype(m_stmtList) &getStmtLists() const;

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

        void print(std::fstream &fout) override;

        GETTER(cond, getCond)

        GETTER(execStmt, getExecStmt)

        GETTER(elseStmt, getElseStmt)

    protected:
        // if cond then execStmt [else elseStmt]
        mathExpr *cond;
        abstractStmt *execStmt;
        abstractStmt *elseStmt;
    };

    class repeatStmt : public abstractStmt {
    public:
        repeatStmt(mathExpr *cond, stmtList *stmtlist) : cond{cond}, stmtlist{stmtlist} {
            n_type = TOY_COMPILER::REPEATSTMT;
        }

        void print(std::fstream &fout) override;

        GETTER(cond, getCond)

        GETTER(stmtlist, getStmtList)

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

        GETTER(cond, getCond)

        GETTER(stmt, getStmt)

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

        GETTER(from, getFrom)

        GETTER(to, getTo)

        GETTER(direction, getDirection)

        GETTER(stmt, getStmt)

    protected:
        //FOR  ID  ASSIGN  from  direction  to  DO stmt
        mathExpr *from;
        mathExpr *to;
        bool direction;
        abstractStmt *stmt;
    };

    class caseNode {
    public:
        // if case_
        constNode *case_;
        mathExpr *expr;
    };

    class caseStmt : public abstractStmt {
    public:
        explicit caseStmt(mathExpr *cond) : case_cond{cond} {
            n_type = TOY_COMPILER::CASESTMT;
        }

        void print(std::fstream &fout) override;

        void addCase(caseExpr *case_expr) const;

        GETTER(case_cond, getCond)

        GETTER(case_expr_list, &getCases)

    protected:
        // CASE expression OF case_expr_list  END
        mathExpr *case_cond;
        std::vector<caseNode *> case_expr_list;
    };

    class gotoStmt : public abstractStmt {
    public:
        explicit gotoStmt(int l) : label{l} {
            n_type = TOY_COMPILER::GOTOSTMT;
        }

        void print(std::fstream &fout) override;

        int getLabel();

    protected:
        int label;
    };

    class assignStmt : public abstractStmt {
//        ID  ASSIGN  expression
//        | ID LB expression RB ASSIGN expression
//        | ID  DOT  ID  ASSIGN  expression


    public:
        explicit assignStmt(abstractExpr *l, abstractExpr *r) : lhs{l}, rhs{r} {
            n_type = TOY_COMPILER::ASSIGNSTMT;
        }

        void print(std::fstream &fout) override;

        GETTER(lhs, getLhs)

        GETTER(rhs, getRhs)

    protected:
        abstractExpr *lhs;
        abstractExpr *rhs;
    };

    class functionNode : public abstractAST {
    public:
        functionNode(std::string name, bool isfunc, std::vector<abstractExpr *> *args, stmtList *body, bool isProc,
                     bool isSys)
                : func_symbol{name, isfunc}, argList{args}, body{body} {
            isProc = isProc;
            isSys = isSys;
            n_type = TOY_COMPILER::FUNCTION;
        }

        void print(std::fstream &fout) override;

        GETTER(func_symbol, getFuncSymbol)

        bool isProc() const;

        bool isSys() const;

        GETTER(argList, getArgs)

        GETTER(body, getBody)

    protected:
        TOY_COMPILER::Symbol func_symbol;
        bool isProc;
        bool isSys;
        std::vector<abstractExpr *> *argList;
        stmtList *body;
    };

    class rootProgram : public abstractAST {
    public:
        rootProgram() {
            n_type = TOY_COMPILER::PROGRAM;
        }

        void addFunc(functionNode *f);

        void addStmt(abstractStmt *stmt);

        void addDecl(abstractTypeDeclNode *decl);

        void print(std::fstream &fout) override;

        GETTER(funcs, &getFuncs)

        GETTER(stmts, &getStmts)

        GETTER(decls, &getDecls)

    public:
        std::vector<functionNode *> funcs;
        std::vector<abstractStmt *> stmts;
        std::vector<abstractTypeDeclNode *> decls;
    };
}

#endif //TOY_COMPILER_AST_H
