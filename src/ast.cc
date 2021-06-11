//
// Created by 薛伟 on 2021/6/11.
//

#include "ast.h"
#include <algorithm>

std::string getJsonString(const std::string& name) {
    return R"({ "name" : ")" + name + "\" }";
}

std::string getJsonString(const std::string& name, const vector<std::string>& children) {
    std::string result = R"({ "name" : ")" + name + R"(", "children" : [ )";
    int i = 0;
    for(auto &child : children) {
        if(i != children.size() - 1)
            result += child + ", ";
        else
            result += child + " ";
        i++;
    }
    return result + " ] }";
}

std::string getJsonString(const std::string& name, const std::string& value) {
    return getJsonString(name, vector<std::string>{value});
}

std::string getJsonString(const std::string& name, const std::string& value, const vector<string>& children) {
    std::string result = R"({ "name" : ")" + name + R"(", "value" : ")" + value + R"(", "children" : [ )";
    int i = 0;
    for(auto &child : children) {
        if(i != children.size() - 1)
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
    auto f = [&](utilsInterface * n) {
        children.push_back(n->getNodeJson());
    };

    for_each(constdecls->begin(), constdecls->end(), f);

    return getJsonString("consetDecl", children);
}

std::string TOY_COMPILER::simpleDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::rangeDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::namesDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::arrayDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::field::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::recordDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::varNode::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::varDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::typeDefDecl::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::parameter::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::variableNode::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::mathExpr::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::stmtList::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::ifStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::repeatStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::whileStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::forStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::caseNode::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::caseStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::gotoStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::assignStmt::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::functionCall::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::functionNode::getNodeJson() {
    return utilsInterface::getNodeJson();
}

std::string TOY_COMPILER::rootProgram::getNodeJson() {
    return utilsInterface::getNodeJson();
}
