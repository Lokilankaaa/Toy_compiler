//
// Created by 薛伟 on 2021/6/11.
//

#include "ast.h"
#include <algorithm>

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

std::string TOY_COMPILER::constNode::getNodeJson() {
    return getJsonString("constNode");
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

std::string TOY_COMPILER::rangeDecl::getNodeJson() {
    return getJsonString("rangeDecl");
}

std::string TOY_COMPILER::namesDecl::getNodeJson() {
    return getJsonString("namesDecl");
}

std::string TOY_COMPILER::arrayDecl::getNodeJson() {
    return getJsonString("arrayDecl");
}

std::string TOY_COMPILER::field::getNodeJson() {
    return getJsonString("field");
}

std::string TOY_COMPILER::recordDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(fields.begin(), fields.end(), f);

    return getJsonString("recordDecl", children);
}

std::string TOY_COMPILER::varNode::getNodeJson() {
    return getJsonString("varNode", varType->getNodeJson());
}

std::string TOY_COMPILER::varDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(decls->begin(), decls->end(), f);

    return getJsonString("varDecls", children);
}

std::string TOY_COMPILER::typeDefDecl::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(new_type->begin(), new_type->end(), f);

    return getJsonString("typeDefDecl", children);
}

std::string TOY_COMPILER::parameter::getNodeJson() {
    return getJsonString("parameter");
}

std::string TOY_COMPILER::variableNode::getNodeJson() {
    return getJsonString("variable");
}

std::string TOY_COMPILER::mathExpr::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(left->getNodeJson());
    children.push_back(getJsonString("operator"));
    children.push_back(right->getNodeJson());

    return getJsonString("recordDecl", children);
}

std::string TOY_COMPILER::stmtList::getNodeJson() {
    std::vector<std::string> children;
    auto f = [&](utilsInterface *n) {
        children.push_back(n->getNodeJson());
    };

    for_each(m_stmtList.begin(), m_stmtList.end(), f);

    return getJsonString("stmtList", children);
}

std::string TOY_COMPILER::ifStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("cond", cond->getNodeJson()));
    children.push_back(getJsonString("execStmt", execStmt->getNodeJson()));
    if (elseStmt != nullptr)
        children.push_back(getJsonString("elseStmt", elseStmt->getNodeJson()));
    return getJsonString("ifStmt", children);
}

std::string TOY_COMPILER::repeatStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("cond", cond->getNodeJson()));
    children.push_back(stmtlist->getNodeJson());

    return getJsonString("repeatStmt", children);
}

std::string TOY_COMPILER::whileStmt::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("cond", cond->getNodeJson()));
    children.push_back(stmtlist->getNodeJson());

    return getJsonString("whileStmt", children);
}

std::string TOY_COMPILER::forStmt::getNodeJson() {
    return getJsonString("forStmt", stmt->getNodeJson());
}

std::string TOY_COMPILER::caseNode::getNodeJson() {
    return getJsonString("caseNode");
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

std::string TOY_COMPILER::gotoStmt::getNodeJson() {
    return getJsonString("gotoStmt");
}

std::string TOY_COMPILER::assignStmt::getNodeJson() {
    return getJsonString("assignStmt");
}

std::string TOY_COMPILER::functionCall::getNodeJson() {
    return getJsonString("functionCall");
}

std::string TOY_COMPILER::functionNode::getNodeJson() {
    std::vector<std::string> children;
    children.push_back(getJsonString("id"));
    children.push_back(getJsonString("paralist"));
    children.push_back(body->getNodeJson());
    children.push_back(getJsonString("returnValue"));

    return getJsonString("functionDecl", children);
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

std::string TOY_COMPILER::utilsInterface::getNodeJson() {
    return "";
}
