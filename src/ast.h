//
// Created by 薛伟 on 2021/5/31.
//

#ifndef TOY_COMPILER_AST_H
#define TOY_COMPILER_AST_H

#include "types.cuh"
#include <iostream>
#include <utility>
#include <vector>
#include <climits>
#include <llvm/IR/Value.h>


#define GETTER(var, method_name) decltype(var) &method_name()

namespace TOY_COMPILER {
    class utilsInterface {
        int lineno;

    public:
        virtual std::string getNodeJson();

        virtual llvm::Value *codeGen();

        void setLineno(int l) { lineno = l; }

        int getLineno() { return lineno; }
    };

    class abstractAST : public utilsInterface {
    public:

        abstractAST *father = nullptr;
        TOY_COMPILER::ASTType n_type;
    };

// mark class
    class abstractSubroutine : public abstractAST {
    };

    class abstractStmt : public abstractAST {
    public:
        abstractStmt() { n_type = TOY_COMPILER::STMT; }
    };

    class abstractExpr : public abstractStmt {
    public:
        abstractExpr() {
            n_type = TOY_COMPILER::EXPRESSION;
            m_value.p = nullptr;
        }

        TOY_COMPILER::expValue m_value;
        TOY_COMPILER::valType res_type;
    };

    class abstractTypeDeclNode : public abstractAST {
    public:
        abstractTypeDeclNode() { n_type = TOY_COMPILER::SIMPLEDCEL; }
    };

// mark class
    class abstractSimpleDecl : public abstractTypeDeclNode {
    };

    class literal : public abstractExpr {
    protected:
        TOY_COMPILER::expValue *_value;
        TOY_COMPILER::const_valueType *_t;

    public:
        literal(TOY_COMPILER::expValue *v, TOY_COMPILER::const_valueType *t) : _t{t} {
            n_type = TOY_COMPILER::LITERAL;
            _value = new TOY_COMPILER::expValue;
            if (_t->sys_type == MAXINT) {
                _value->int_value = INT_MAX;
            } else if (_t->sys_type == TRUE) {
                _value->bool_value = true;
            } else if (_t->sys_type == FALSE) {
                _value->bool_value = false;
            } else {
                _value = v;
            }
        }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;

        GETTER(_t, getType) { return _t; }

        GETTER(_value, getValue) { return _value; }
    };

    class constNode : public utilsInterface {
        // NAME  EQUAL  const_value
    protected:
        std::string id;
        literal *val;

    public:
        constNode(std::string id, literal *v) : id{std::move(id)}, val{v} {}

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;

        GETTER(id, getId) { return id; }

        GETTER(val, getType) { return val; }
    };

    class constDecl : public abstractTypeDeclNode {
        // CONST const_expr_list  NAME  EQUAL  const_value  SEMI
    protected:
        std::vector<constNode *> *constdecls;

    public:
        constDecl() {
            n_type = TOY_COMPILER::CONSTDECL;
            constdecls = new std::vector<constNode *>();
        }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;

        void addConstDecl(const std::string &id, literal *v) {
            constdecls->push_back(new constNode(id, v));
        }

        GETTER(constdecls, getDecls) { return constdecls; }
    };

    class simpleDecl : public abstractSimpleDecl {
    protected:
        TOY_COMPILER::valType val_type;

    public:
        // simple_type_decl:   sys_type
        simpleDecl(TOY_COMPILER::valType t) : val_type{t} {}

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;

        GETTER(val_type, getval_type) { return val_type; }
    };

    class rangeDecl : public abstractSimpleDecl {
    protected:
        std::string id_l, id_r;
        literal *con_l, *con_r;
        bool minus_l, minus_r;

    public:
        // simple_type_decl:   NAME  DOTDOT  NAME
        rangeDecl(std::string l, std::string r)
                : id_l{std::move(l)}, id_r{std::move(r)} {
            n_type = TOY_COMPILER::RANGEDECL;
        }

        // simple_type_decl:  const_value  DOTDOT  const_value
        //                |  MINUS  const_value  DOTDOT  const_value
        //                |  MINUS  const_value  DOTDOT  MINUS  const_value
        rangeDecl(bool m_l, literal *c_l, bool m_r, literal *c_r)
                : minus_l{m_l}, con_l{c_l}, minus_r{m_r}, con_r{c_r} {}

        GETTER(con_l, getLeftRange) { return con_l; }

        GETTER(con_r, getRightRange) { return con_r; }

        GETTER(minus_l, getLeftSign) { return minus_l; }

        GETTER(minus_r, getRightSign) { return minus_r; }

        GETTER(id_l, getId_l) { return id_l; }

        GETTER(id_r, getId_r) { return id_r; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    //alias enumDecl
    class namesDecl : public abstractSimpleDecl {
    protected:
        std::vector<std::string> names;
        bool isnamelist;

    public:
        // simple_type_decl ：  NAME  |  LP  name_list  RP  (can judge whether NAME
        // or name_list by the length of vector)
        // actually enum type [apple, banana,....] == [1,2,...]
        namesDecl(std::vector<std::string> names, bool islist)
                : names{std::move(names)}, isnamelist{islist} {
            n_type = TOY_COMPILER::NAMEDECL;
        }

        void addName(const std::string &name) { names.push_back(name); }

        std::string getNodeJson() override;

        GETTER(names, getNames) { return names; }

        GETTER(isnamelist, getIsNamelist) { return isnamelist; }

        llvm::Value *codeGen() override;
    };

    class arrayDecl : public abstractTypeDeclNode {
    protected:
        abstractSimpleDecl *sim_type;
        abstractTypeDeclNode *type_decl;

    public:
        // ARRAY  LB  simple_type_decl  RB  OF  type_decl
        arrayDecl(abstractSimpleDecl *sim_types, abstractTypeDeclNode *type_decl)
                : sim_type{sim_types}, type_decl{type_decl} {
            n_type = TOY_COMPILER::ARRAYDECL;
        }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;

        GETTER(sim_type, getSimpleType) { return sim_type; }

        GETTER(type_decl, getTypeDecl) { return type_decl; }
    };

    class field : public utilsInterface {
    protected:
        std::vector<std::string> *namelist;
        abstractTypeDeclNode *type;

    public:
        field(std::vector<std::string> *ns, abstractTypeDeclNode *t)
                : namelist{ns}, type{t} {}

        GETTER(namelist, getNamelist) { return namelist; }

        GETTER(type, getType) { return type; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class recordDecl : public abstractTypeDeclNode {
    protected:
        std::vector<field *> fields;

    public:
        recordDecl() { n_type = TOY_COMPILER::RECORDDECL; }

        void addRecord(field r) { fields.push_back(&r); }

        GETTER(fields, getFields) { return fields; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class varNode : public utilsInterface {
    protected:
        std::vector<std::string> *names;
        abstractTypeDeclNode *varType;

    public:
        varNode(std::vector<std::string> *ns, abstractTypeDeclNode *inferType)
                : names{ns}, varType{inferType} {}

        GETTER(names, getNames) { return names; }

        GETTER(varType, getVarType) { return varType; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class varDecl : public abstractTypeDeclNode {
    protected:
        std::vector<varNode *> *decls;

    public:
        varDecl() {
            n_type = TOY_COMPILER::VARDECL;
            decls = new std::vector<varNode *>();
        }

        void addDecl(varNode *v) { decls->push_back(v); }

        GETTER(decls, getDecls) { return decls; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class typeDefDecl : public abstractTypeDeclNode {
    protected:
        std::vector<varNode *> *new_type;

    public:
        typeDefDecl() { n_type = TOY_COMPILER::TYPEDEF; }

        void addTypeDef(varNode *d) { new_type->push_back(d); }

        GETTER(new_type, getNewType) { return new_type; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class parameter : public utilsInterface {
    protected:
        TOY_COMPILER::passBy by;
        std::vector<std::string> names; // names specifies whether it's nameslist or
        // name if the length is not 0
        abstractSimpleDecl *simple_type;

    public:
        parameter(TOY_COMPILER::passBy b, std::vector<std::string> ns,
                  abstractSimpleDecl *t)
                : names{std::move(ns)}, by{b}, simple_type{t} {}

        GETTER(by, getPassBy) { return by; }

        GETTER(names, getNames) { return names; }

        GETTER(simple_type, getSimpleType) { return simple_type; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class variableNode : public abstractExpr {
    protected:
        std::string id;

    public:
        variableNode(std::string name) : id{std::move(name)} {
            n_type = TOY_COMPILER::VARIABLE;
        }

        GETTER(id, getId) { return id; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class mathExpr : public abstractExpr {
    protected:
        TOY_COMPILER::opType type;
        abstractExpr *left;
        abstractExpr *right;

    public:
        // +, -, *, /, , %, &, |, !, -(num), >, >=, <, <=, <>, [], .

        mathExpr(TOY_COMPILER::opType t, abstractExpr *l, abstractExpr *r)
                : type{t}, left{l}, right{r} {
            n_type = TOY_COMPILER::MATHEXPR;
        }

        GETTER(left, getLeftChild) { return left; }

        GETTER(right, getRightChild) { return right; }

        GETTER(type, getOp) { return type; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class stmtList : public abstractStmt {
    protected:
        std::vector<abstractStmt *> m_stmtList;

    public:
        stmtList() { n_type = TOY_COMPILER::STMTLIST; }

        void addStmt(abstractStmt *stmt) { m_stmtList.push_back(stmt); }

        GETTER(m_stmtList, getStmtList) { return m_stmtList; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class ifStmt : public abstractStmt {
    protected:
        // if cond then execStmt [else elseStmt]
        abstractExpr *cond;
        abstractStmt *execStmt;
        abstractStmt *elseStmt;

    public:
        ifStmt(abstractExpr *cond, abstractStmt *execStmt, abstractStmt *elseStmt)
                : cond{cond}, execStmt{execStmt}, elseStmt{elseStmt} {
            n_type = TOY_COMPILER::IFSTMT;
        }

        GETTER(cond, getCond) { return cond; }

        GETTER(execStmt, getExecStmt) { return execStmt; }

        GETTER(elseStmt, getElseStmt) { return elseStmt; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class repeatStmt : public abstractStmt {
    protected:
        // repeat stmtlists until cond
        stmtList *stmtlist;
        abstractExpr *cond;

    public:
        repeatStmt(abstractExpr *cond, stmtList *stmtlist)
                : cond{cond}, stmtlist{stmtlist} {
            n_type = TOY_COMPILER::REPEATSTMT;
        }

        GETTER(cond, getCond) { return cond; }

        GETTER(stmtlist, getStmtList) { return stmtlist; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class whileStmt : public abstractStmt {
    protected:
        // while cond do stmt
        abstractStmt *stmtlist;
        abstractExpr *cond;

    public:
        whileStmt(abstractExpr *cond, abstractStmt *stmts) : cond{cond}, stmtlist{stmts} {
            n_type = TOY_COMPILER::WHILESTMT;
        }

        GETTER(cond, getCond) { return cond; }

        GETTER(stmtlist, getStmtlist) { return stmtlist; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class forStmt : public abstractStmt {
    protected:
        // FOR  ID  ASSIGN  from  direction  to  DO stmt
        std::string id;
        abstractExpr *from;
        abstractExpr *to;
        bool direction;
        abstractStmt *stmt;

    public:
        forStmt(std::string i, abstractExpr *from, abstractExpr *to, bool direction,
                abstractStmt *s)
                : id{i}, from{from}, to{to}, direction{direction}, stmt{s} {
            n_type = TOY_COMPILER::FORSTMT;
        }

        GETTER(id, getId) { return id; }

        GETTER(from, getFrom) { return from; }

        GETTER(to, getTo) { return to; }

        GETTER(direction, getDirection) { return direction; }

        GETTER(stmt, getStmtlist) { return stmt; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class caseNode : public utilsInterface {
    public:
        abstractExpr *case_;
        abstractStmt *stmt;

        // if case_
        caseNode(abstractExpr *c, abstractStmt *s) : case_{c}, stmt{s} {}

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class caseStmt : public abstractStmt {
    protected:
        // CASE expression OF case_expr_list  END
        abstractExpr *case_cond;
        std::vector<caseNode *> case_expr_list;

    public:
        caseStmt() { n_type = TOY_COMPILER::CASESTMT; }

        void addCond(abstractExpr *cond) { case_cond = cond; }

        void print(std::fstream &fout);

        void addCase(caseNode *case_expr) { case_expr_list.push_back(case_expr); }

        GETTER(case_cond, getCond) { return case_cond; }

        GETTER(case_expr_list, getCases) { return case_expr_list; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class gotoStmt : public abstractStmt {
    protected:
        int label;

    public:
        explicit gotoStmt(int l) : label{l} { n_type = TOY_COMPILER::GOTOSTMT; }

        void print(std::fstream &fout);

        int getLabel() const { return label; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class assignStmt : public abstractStmt {
        //        ID  ASSIGN  expression
        //        | ID LB expression RB ASSIGN expression
        //        | ID  DOT  ID  ASSIGN  expression
    protected:
        abstractExpr *lhs;
        abstractExpr *rhs;

    public:
        explicit assignStmt(abstractExpr *l, abstractExpr *r) : lhs{l}, rhs{r} {
            n_type = TOY_COMPILER::ASSIGNSTMT;
        }

        GETTER(lhs, getLhs) { return lhs; }

        GETTER(rhs, getRhs) { return rhs; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class functionCall : public abstractExpr {
    protected:
        std::string func_name;
        std::vector<abstractExpr *> *args;

    public:
        functionCall(std::string name, std::vector<abstractExpr *> *a)
                : func_name{std::move(name)}, args{a} {
            n_type = TOY_COMPILER::FUNCCALL;
        }

        GETTER(func_name, getFunc_name) { return func_name; }

        GETTER(args, getArgs) { return args; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class functionNode : public abstractAST {
    protected:
        std::string id;
        std::vector<parameter *> *paralist;
        abstractSubroutine *body;
        abstractSimpleDecl *retval;
        bool isprocedure; // whether it's procedure;

    public:
        functionNode(std::string id, std::vector<parameter *> *args,
                     abstractSubroutine *body, abstractSimpleDecl *ret)
                : id{std::move(id)}, paralist{args}, retval{ret}, body{body} {
            n_type = TOY_COMPILER::FUNCTION;
        }

        functionNode(std::string id, std::vector<parameter *> *args,
                     abstractSubroutine *body)
                : id{std::move(id)}, paralist{args}, body{body} {
            n_type = TOY_COMPILER::FUNCTION;
            isprocedure = true;
        }

        GETTER(id, getId) { return id; }

        GETTER(paralist, getParams) { return paralist; }

        GETTER(body, getBody) { return body; }

        GETTER(retval, getRetval) { return retval; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };

    class rootProgram :public abstractSubroutine {
    public:
        std::vector<functionNode *> funcs;
        stmtList stmts;
        std::vector<abstractTypeDeclNode *> decls;

    public:
        rootProgram() { n_type = TOY_COMPILER::PROGRAM; }

        void addFunc(functionNode *f) { funcs.push_back(f); }

        void addStmt(abstractStmt *stmt) { stmts.addStmt(stmt); }

        void addDecl(abstractTypeDeclNode *decl) { decls.push_back(decl); }

        GETTER(funcs, getFuncs) { return funcs; }

        GETTER(stmts, getStmts) { return stmts; }

        GETTER(decls, getDecls) { return decls; }

        std::string getNodeJson() override;

        llvm::Value *codeGen() override;
    };
} // namespace TOY_COMPILER

#endif // TOY_COMPILER_AST_H
