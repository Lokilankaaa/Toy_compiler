//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_AST_H
#define TOY_COMPILER_AST_H

#include "types.cuh"
#include <iostream>
#include <utility>
#include <vector>

#define GETTER(var, method_name) decltype(var) method_name() const

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
        constNode(std::string id, TOY_COMPILER::const_valueTye t) : id{std::move(id)}, const_type{t} {

        }

        GETTER(id, getId) {
            return id;
        }

        GETTER(const_type, getType) {
            return const_type;
        }

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

        void addConstDecl(const std::string &id, TOY_COMPILER::const_valueTye t) {
            constdecls.push_back(new constNode(id, t));
        }

        GETTER(constdecls, getDecls) {
            return constdecls;
        }

    protected:
        std::vector<constNode *> constdecls;
    };

    class simpleDecl : public abstractTypeDeclNode, public abstractSimpleDecl {
    public:
        // simple_type_decl:   sys_type
        simpleDecl(std::string id, TOY_COMPILER::valType t) : id{std::move(id)}, val_type{t} {

        }

        GETTER(id, getId) {
            return id;
        }

        GETTER(val_type, getval_type) {
            return val_type;
        }

    protected:
        TOY_COMPILER::valType val_type;
        std::string id;
    };

    class rangeDecl : public abstractTypeDeclNode, public abstractSimpleDecl {
    public:
        // simple_type_decl:   NAME  DOTDOT  NAME
        rangeDecl(std::string id, std::string l, std::string r) : id{std::move(id)},
                                                                  id_l{std::move(l)},
                                                                  id_r{std::move(r)} {
            n_type = TOY_COMPILER::RANGEDECL;
        }


        //simple_type_decl:  const_value  DOTDOT  const_value
        //                |  MINUS  const_value  DOTDOT  const_value
        //                |  MINUS  const_value  DOTDOT  MINUS  const_value
        rangeDecl(std::string id, bool m_l, const_valueType c_l, bool m_r, const_valueType c_r) : id{std::move(id)},
                                                                                                  minus_l{m_l},
                                                                                                  con_l{c_l},
                                                                                                  minus_r{m_r},
                                                                                                  con_r{c_r} {

        }

        GETTER(id, getId) {
            return id;
        }

        GETTER(con_l, getLeftRange) {
            return con_l;
        }

        GETTER(con_r, getRightRange) {
            return con_r;
        }

        GETTER(minus_l, getLeftSign) {
            return minus_l;
        }

        GETTER(minus_r, getRightSign) {
            return minus_r;
        }

    protected:
        std::string id, id_l, id_r;
        TOY_COMPILER::const_valueType *con_l, *con_r;
        bool minus_l, minus_r;
    };

    class namesDecl : public abstractTypeDeclNode, public abstractSimpleDecl {
    public:
        //simple_type_decl ：  NAME  |  LP  name_list  RP  (can judge whether NAME or name_list by the length of vector)
        namesDecl(std::string id, std::vector<std::string> names) : id{std::move(id)}, names{std::move(names)} {
            n_type = TOY_COMPILER::NAMEDECL;
        }

        void addName(const std::string &name) {
            names.push_back(name);
        }

        GETTER(id, getId) {
            return id;
        }

        GETTER(names, getNames) {
            return names;
        }

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

        GETTER(id, getId) {
            return id;
        }

        GETTER(sim_type, getSimpleType) {
            return sim_type;
        }

        GETTER(type_decl, getTypeDecl) {
            return type_decl;
        }

    protected:
        std::string id;
        abstractSimpleDecl *sim_type;
        abstractTypeDeclNode *type_decl;
    };

    class record {
    public:
        record(const std::vector<std::string> &ns, const std::vector<abstractTypeDeclNode *> &ts) {
            _record = std::make_pair(ns, ts);
        }

        GETTER(_record, getDetail) {
            return _record;
        }

    protected:
        std::pair<std::vector<std::string>, std::vector<abstractTypeDeclNode *> > _record;
    };

    class recordDecl : public abstractTypeDeclNode {
    public:
        recordDecl() {
            n_type = TOY_COMPILER::RECORDDECL;
        }

        void addRecord(record r) {
            records.push_back(&r);
        }

        GETTER(records, getRecords) {
            return records;
        }

    protected:
        std::vector<record *> records;
    };

    class varNode {
    public:
        varNode(std::string id, abstractTypeDeclNode *inferType) : id{std::move(id)}, varType{inferType} {

        }

        GETTER(id, getId) {
            return id;
        }

        GETTER(varType, getVarType) {
            return varType;
        }

    protected:
        std::string id;
        abstractTypeDeclNode *varType;
    };

    class varDecl : public abstractTypeDeclNode {
    public:
        varDecl() {
            n_type = TOY_COMPILER::VARDECL;
        }

        void addDecl(varNode *v) {
            decls.push_back(v);
        }

        GETTER(decls, getDecls) {
            return decls;
        }

    protected:
        std::vector<varNode *> decls;
    };

    class mathExpr : public abstractExpr {
    public:
        // +, -, *, /, , %, &, |, !, -(num), >, >=, <, <=, <>
        void print(std::fstream &fout) override;

        mathExpr(TOY_COMPILER::opType t, mathExpr *l, mathExpr *r) : type{t}, left{l}, right{r} {}

        GETTER(left, getLeftChild) {
            return left;
        }

        GETTER(right, getRightChild) {
            return right;
        }

        GETTER(type, getOp) {
            return type;
        }

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

        void addStmt(abstractStmt *stmt) {
            m_stmtList.push_back(stmt);
        }

        GETTER(m_stmtList, getStmtList) {
            return m_stmtList;
        }

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

        GETTER(cond, getCond) {
            return cond;
        }

        GETTER(execStmt, getExecStmt) {
            return execStmt;
        }

        GETTER(elseStmt, getElseStmt) {
            return elseStmt;
        }

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

        GETTER(cond, getCond) {
            return cond;
        }

        GETTER(stmtlist, getStmtList) {
            return stmtlist;
        }

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

        GETTER(cond, getCond) {
            return cond;
        }

        GETTER(stmtlist, getStmtlist) {
            return stmtlist;
        }

    protected:
        // while cond do stmt
        stmtList *stmtlist;
        mathExpr *cond;
    };

    class forStmt : public abstractStmt {
    public:
        forStmt(mathExpr *from, mathExpr *to, bool direction, abstractStmt *stmt) : from{from}, to{to},
                                                                                    direction{direction}, stmt{stmt} {
            n_type = TOY_COMPILER::FORSTMT;
        }

        void print(std::fstream &fout) override;

        GETTER(from, getFrom) {
            return from;
        }

        GETTER(to, getTo) {
            return to;
        }

        GETTER(direction, getDirection) {
            return direction;
        }

        GETTER(stmtlist, getStmtlist) {
            return stmtlist;
        }

    protected:
        //FOR  ID  ASSIGN  from  direction  to  DO stmt
        mathExpr *from;
        mathExpr *to;
        bool direction;
        stmtList *stmtlist;
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

        void addCase(caseNode *case_expr) const {
            case_expr_list.push_back(case_expr);
        }

        GETTER(case_cond, getCond) {
            return cond
        }

        GETTER(case_expr_list, getCases) {
            return case_expr_list;
        }

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

        int getLabel() {
            return label;
        }

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

        GETTER(lhs, getLhs) {
            return lhs;
        }

        GETTER(rhs, getRhs) {
            return rhs;
        }

    protected:
        abstractExpr *lhs;
        abstractExpr *rhs;
    };

    class functionNode : public abstractAST {
    public:
        functionNode(std::string id, std::vector<abstractExpr *> *args, stmtList *body, bool isproc,
                     bool issys)
                : id{std::move(id)}, _isSys{issys}, _isProc{isproc}, argList{args}, body{body} {
            isProc = isProc;
            isSys = isSys;
            n_type = TOY_COMPILER::FUNCTION;
        }

        void print(std::fstream &fout) override;

        bool isProc() const {
            return _isProc;
        }

        bool isSys() const {
            return _isSys;
        }

        GETTER(id, getId) {
            return id;
        }

        GETTER(argList, getArgs) {
            return argList;
        }

        GETTER(body, getBody) {
            return body;
        }

    protected:
        std::string id;
        bool _isProc;
        bool _isSys;
        std::vector<abstractExpr *> *argList;
        stmtList *body;
    };

    class rootProgram : public abstractAST {
    public:
        rootProgram() {
            n_type = TOY_COMPILER::PROGRAM;
        }

        void addFunc(functionNode *f) {
            funcs.push_back(f);
        }

        void addStmt(abstractStmt *stmt) {
            stmts.push_back(stmt);
        }

        void addDecl(abstractTypeDeclNode *decl) {
            decls.push_back(decl);
        }

        void print(std::fstream &fout) override;

        GETTER(funcs, &getFuncs) {
            return funcs;
        }

        GETTER(stmts, &getStmts) {
            return stmts;
        }

        GETTER(decls, &getDecls) {
            return decls;
        }

    public:
        std::vector<functionNode *> funcs;
        stmtList stmts;
        std::vector<abstractTypeDeclNode *> decls;
    };
}

#endif //TOY_COMPILER_AST_H
