//
// Created by 薛伟 on 2021/6/11.
//

#include "ast.h"
#include <algorithm>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> TheBuilder(TheContext);

std::string getJsonString(const std::string &name) {
    return R"({ "name" : ")" + name + "\" }";
}

std::string getJsonString(const std::string &name, const std::vector<std::string> &children) {
    std::string result = R"({ "name" : ")" + name + R"(", "children" : [ )";
    int i = 0;
    for (auto &child : children) {
        if (i != children.size() - 1)
            result += child + ", ";
        else
            result += child + " ";
        i++;
    }
    return result + " ] }";
}

std::string getJsonString(const std::string &name, const std::string &value) {
    return getJsonString(name, std::vector<std::string>{value});
}

std::string getJsonString(const std::string &name, const std::string &value, const std::vector<std::string> &children) {
    std::string result = R"({ "name" : ")" + name + R"(", "value" : ")" + value + R"(", "children" : [ )";
    int i = 0;
    for (auto &child : children) {
        if (i != children.size() - 1)
            result += child + ", ";
        else
            result += child + " ";
        i++;
    }
    return result + " ] }";
}

std::string TOY_COMPILER::literal::getNodeJson() {
    return getJsonString("literal");
}

llvm::Value *TOY_COMPILER::literal::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::constNode::getNodeJson() {
    return getJsonString("constNode");
}

llvm::Value *TOY_COMPILER::constNode::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::constDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(constdecls->begin(), constdecls->end(), f);

    return getJsonString("consetDecl", children);
}

std::string TOY_COMPILER::simpleDecl::getNodeJson() {
    return getJsonString("simpleDecl");
}

llvm::Value *TOY_COMPILER::simpleDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::rangeDecl::getNodeJson() {
    return getJsonString("rangeDecl");
}

llvm::Value *TOY_COMPILER::rangeDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::namesDecl::getNodeJson() {
    return getJsonString("namesDecl");
}

llvm::Value *TOY_COMPILER::namesDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::arrayDecl::getNodeJson() {
    return getJsonString("arrayDecl");
}

llvm::Value *TOY_COMPILER::arrayDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::field::getNodeJson() {
    return getJsonString("field");
}

llvm::Value *TOY_COMPILER::field::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::recordDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(fields.begin(), fields.end(), f);

    return getJsonString("recordDecl", children);
}

llvm::Value *TOY_COMPILER::recordDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::varNode::getNodeJson() {
    return getJsonString("varNode", varType->getNodeJson());
}

llvm::Value *TOY_COMPILER::varNode::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::varDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(decls->begin(), decls->end(), f);

    return getJsonString("varDecls", children);
}

llvm::Value *TOY_COMPILER::varDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::typeDefDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(new_type->begin(), new_type->end(), f);

    return getJsonString("typeDefDecl", children);
}

llvm::Value *TOY_COMPILER::typeDefDecl::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::parameter::getNodeJson() {
    return getJsonString("parameter");
}

llvm::Value *TOY_COMPILER::parameter::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::variableNode::getNodeJson() {
    return getJsonString("variable");
}

llvm::Value *TOY_COMPILER::variableNode::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::mathExpr::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(left->getNodeJson());
    children.push_back(getJsonString("operator"));
    children.push_back(right->getNodeJson());

    return getJsonString("recordDecl", children);
}

llvm::Value *TOY_COMPILER::mathExpr::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::stmtList::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(m_stmtList.begin(), m_stmtList.end(), f);

    return getJsonString("stmtList", children);
}

llvm::Value *TOY_COMPILER::stmtList::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::ifStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("cond", cond->getNodeJson()));
    children.push_back(getJsonString("execStmt", execStmt->getNodeJson()));
    if (elseStmt != nullptr)
        children.push_back(getJsonString("elseStmt", elseStmt->getNodeJson()));
    return getJsonString("ifStmt", children);
}

llvm::Value *TOY_COMPILER::ifStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::repeatStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("cond", cond->getNodeJson()));
    children.push_back(stmtlist->getNodeJson());

    return getJsonString("repeatStmt", children);
}

llvm::Value *TOY_COMPILER::repeatStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::whileStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("cond", cond->getNodeJson()));
    children.push_back(stmtlist->getNodeJson());

    return getJsonString("whileStmt", children);
}

llvm::Value *TOY_COMPILER::whileStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::forStmt::getNodeJson() {
    return getJsonString("forStmt", stmt->getNodeJson());
}

llvm::Value *TOY_COMPILER::forStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::caseNode::getNodeJson() {
    return getJsonString("caseNode");
}

llvm::Value *TOY_COMPILER::caseNode::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::caseStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("case_cond", case_cond->getNodeJson()));
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(case_expr_list.begin(), case_expr_list.end(), f);

    return getJsonString("caseStmt", children);
}

llvm::Value *TOY_COMPILER::caseStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::gotoStmt::getNodeJson() {
    return getJsonString("gotoStmt");
}

llvm::Value *TOY_COMPILER::gotoStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::assignStmt::getNodeJson() {
    return getJsonString("assignStmt");
}

llvm::Value *TOY_COMPILER::assignStmt::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::functionCall::getNodeJson() {
    return getJsonString("functionCall");
}

llvm::Value *TOY_COMPILER::functionCall::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::functionNode::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("id"));
    children.push_back(getJsonString("paralist"));
    children.push_back(body->getNodeJson());
    children.push_back(getJsonString("returnValue"));

    return getJsonString("functionDecl", children);
}

llvm::Value *TOY_COMPILER::functionNode::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::rootProgram::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        if (n)
            children.push_back(n->getNodeJson());
    };

    for_each(decls.begin(), decls.end(), f);
    for_each(funcs.begin(), funcs.end(), f);
    children.push_back(stmts.getNodeJson());

    return getJsonString("rootProgram", children);
}

llvm::Value *TOY_COMPILER::rootProgram::codeGen() {
    return utilsInterface::codeGen();
}

std::string TOY_COMPILER::utilsInterface::getNodeJson() {
    return "";
}

llvm::Value *TOY_COMPILER::utilsInterface::codeGen() {
    return nullptr;
}
