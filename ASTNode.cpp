#include <iostream>
#include <vector>
#include "ASTType.h"
#include "ASTNode.h"

ASTNode::children;

public:
    NodeType getType(){
        return ASTNode::type;
    };

    void setNodeType(NodeType _type){
        type = _type;
    }

    virtual std::string toString(unsigned int tabLevel) {
        return nullptr;
    }

    std::vector<ASTNode *> getChildren(){
        return children;
    }

    void setChildren(std::vector<ASTNode *> _children){
        children = std::move(_children);
    }

private:
    NodeType type;
};

class ProgramNode : public ASTNode{
    NodeType type = Program;

public :
    explicit ProgramNode(std::vector<ASTNode *> _body){
        setChildren(std::move(_body));
        setNodeType(type);
    }

    std::string toString(unsigned int tabLevel) override {
        tabLevel = 0;
        tabLevel++;
        std::string output = "type: 'Program',\nbody: [{\n";
        for (auto &child : getChildren()){
            output += child->toString(tabLevel);
        }
        output += "}];\n";
        return output;
    }

};

class ExpressionStatementNode : public ASTNode{
    NodeType type = ExpressionStatement;

public :
    explicit ExpressionStatementNode(std::vector<ASTNode *> _expressions){
        setChildren(std::move(_expressions));
        setNodeType(type);
    }

    std::string toString(unsigned int tabLevel) override {
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
};

class CallExpressionNode : public ASTNode{
    NodeType type = CallExpression;
    ASTNode * callee;

public:
    CallExpressionNode(ASTNode * _callee, std::vector<ASTNode *> _args) {
        callee = _callee;
        setChildren(std::move(_args));
        setNodeType(type);
    }

    std::string toString(unsigned int tabLevel) override {
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
};

class IdentifierNode : public ASTNode{
    NodeType type = Identifier;
    std::string value;

public:
    explicit IdentifierNode(std::string _value){
        value = std::move(_value);
        setNodeType(type);
    }

    std::string toString(unsigned int tabLevel) override {
        std::string tabSpacing = std::string(tabLevel * 4, ' ');
        std::string output  = tabSpacing + "type: 'Identifier',{\n" + tabSpacing + "    name: " + value + "\n" + tabSpacing + "}\n";
        return output;
    }

    std::string getString(){
        return value;
    }
};

class NumberLiteralNode: public ASTNode{
    NodeType type = NumberLiteral;
    int value;

public:
    explicit NumberLiteralNode(int _value){
        value = _value;
        setNodeType(type);
    }

    std::string toString(unsigned int tabLevel) override {
        std::string tabSpacing = std::string(tabLevel * 4, ' ');
        std::string output = tabSpacing + "type: 'NumberLiteral',{\n" + tabSpacing + "    value: " + std::to_string(value) + "\n" + tabSpacing + "}\n";
        return output;
    }

    int getValue(){
        return value;
    }
};
