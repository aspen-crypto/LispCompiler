#include <iostream>
#include <vector>
#include "ASTNode.h"

NodeType ASTNode::getType() {
 return type;
};

void ASTNode::setNodeType(NodeType _type){
        type = _type;
}

std::string ASTNode::toString(unsigned int tabLevel) {
        return nullptr;
}

std::vector<ASTNode *> ASTNode::getChildren(){
        return children;
}

void ASTNode::setChildren(std::vector<ASTNode *> _children){
    children = std::move(_children);
}

ProgramNode::ProgramNode(std::vector<ASTNode *> _body){
    setChildren(std::move(_body));
    setNodeType(Program);
}

std::string ProgramNode::toString(unsigned int tabLevel) {
    tabLevel = 0;
    tabLevel++;
    std::string output = "type: 'Program',\nbody: [{\n";
    for (auto &child : getChildren()){
        output += child->toString(tabLevel);
    }
    output += "}];\n";
    return output;
}


ExpressionStatementNode::ExpressionStatementNode(std::vector<ASTNode *> _expressions){
    setChildren(std::move(_expressions));
    setNodeType(ExpressionStatement);
}

std::string ExpressionStatementNode::toString(unsigned int tabLevel) {
    std::string tabSpacing = std::string(tabLevel * 4, ' ');
    tabLevel++;
    std::string output = tabSpacing + "type: 'ExpressionStatement',\n";
    tabSpacing = std::string(tabLevel * 4, ' ');
    output += tabSpacing + "expression: {\n";
    tabLevel++;
    for(auto expression : getChildren()){
        output += expression -> toString(tabLevel);
    }
    output += tabSpacing + "}\n";
    return output;
}


CallExpressionNode::CallExpressionNode(ASTNode * _callee, std::vector<ASTNode *> _args) {
    callee = _callee;
    setChildren(std::move(_args));
    setNodeType(CallExpression);
}

std::string CallExpressionNode::toString(unsigned int tabLevel) {
    std::string tabSpacing = std::string(tabLevel * 4, ' ');
    tabLevel++;
    std::string output = tabSpacing + "type: 'CallExpression',{\n";
    tabSpacing = std::string(tabLevel * 4, ' ');
    tabLevel ++;
    output += tabSpacing + "callee: {\n" + callee -> toString(tabLevel) + tabSpacing + "}\n" + tabSpacing + "args: {\n";
    for(auto &i : getChildren()){
        output += i -> toString(tabLevel);
    }
    output += tabSpacing + "}\n";
    tabLevel -= 2;
    tabSpacing = std::string(tabLevel * 4, ' ');
    output += tabSpacing + "}\n";
    return output;
};

ASTNode * CallExpressionNode::getCallee() {
    return callee;
};


IdentifierNode::IdentifierNode(std::string _value){
    value = std::move(_value);
    setNodeType(Identifier);
}

std::string IdentifierNode::toString(unsigned int tabLevel) {
    std::string tabSpacing = std::string(tabLevel * 4, ' ');
    std::string output  = tabSpacing + "type: 'Identifier',{\n" + tabSpacing + "    name: " + value + "\n" + tabSpacing + "}\n";
    return output;
}

std::string IdentifierNode::getValue(){
    return value;
}


NumberLiteralNode::NumberLiteralNode(int _value){
    value = _value;
    setNodeType(NumberLiteral);
}

std::string NumberLiteralNode::toString(unsigned int tabLevel) {
    std::string tabSpacing = std::string(tabLevel * 4, ' ');
    std::string output = tabSpacing + "type: 'NumberLiteral',{\n" + tabSpacing + "    value: " + std::to_string(value) + "\n" + tabSpacing + "}\n";
    return output;
}

int NumberLiteralNode::getValue(){
    return value;
}
