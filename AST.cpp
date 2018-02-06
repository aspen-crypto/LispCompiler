#include "AST.h"
#include <iostream>
#include <vector>

class ASTNode;

class AST {
    ASTNode parent;
    std::vector<ASTNode> children;

    ASTNode createNode(){
        return NULL;
    }
};

class ASTNode {
    class Program;
    class BodyNode;

    public:
        enum NodeType {Program, ExpressionStatement, CallExpression, Identifier, NumberLiteral};

        virtual NodeType getType();

        virtual std::string toString(unsigned int tabLevel);

    private:
        class Program : ASTNode{
            NodeType type = ASTNode::Program;
            std::vector<ASTNode *> body;

            public :
                Program(std::vector<ASTNode *> _body){
                    type = ASTNode::Program;
                    body = _body;
                }

                std::string toString(unsigned int tabLevel = 0) override {
                    tabLevel = 0;
                    tabLevel++;
                    std::string output = "type: 'Program',\nbody: [{\n";
                    for (auto &child : body){
                        output += child->toString(tabLevel);
                    }
                    output += "\n}];";
                    return output;
                }

                NodeType getType() override {
                    return type;
                }

        };

        class ExpressionStatement : ASTNode{
            NodeType type = ASTNode::ExpressionStatement;
            std::vector<ASTNode *> expressions;

            public :
                ExpressionStatement(std::vector<ASTNode *> _expressions){
                    expressions = _expressions;
                }

                std::string toString(unsigned int tabLevel) override {
                    std::string tabSpacing = std::string(tabLevel * 4, ' ');
                    tabLevel++;
                    std::string output = tabSpacing + "type: 'ExpressionStatement',\n";
                    tabSpacing = std::string(tabLevel * 4, ' ');
                    output += tabSpacing + "expression: {\n";
                    tabLevel++;
                    for(auto expression : expressions){
                        output += expression -> toString(tabLevel);
                    }
                    output += tabSpacing + "}\n";
                    return output;
                }

                NodeType getType() override {
                    return type;
                }
        };

        class CallExpression : ASTNode{
            NodeType type = ASTNode::CallExpression;
            ASTNode * callee;
            std::vector<ASTNode *> args;

            public:
                CallExpression(ASTNode * _callee, std::vector<ASTNode *> _args) {
                    callee = _callee;
                    args = _args;
                }

                std::string toString(unsigned int tabLevel) override {
                    std::string tabSpacing = std::string(tabLevel * 4, ' ');
                    tabLevel++;
                    std::string output = tabSpacing + "type: 'CallExpression',\n" + tabSpacing + "callee: {\n" + callee -> toString(tabLevel) + tabSpacing + "}\n" + tabSpacing + "args: {";
                    for(auto &i : args){
                        output += i -> toString(tabLevel);
                    }

                };
        };

        class Identifier : ASTNode{
            NodeType type = ASTNode::Identifier;
            std::string value;

            public:
                Identifier(std::string _value){
                    value = _value;
                }

                std::string toString(unsigned int tabLevel) override {
                    std::string tabSpacing = std::string(tabLevel * 4, ' ');
                    std::string output  = "type: 'Identifier',\n" + tabSpacing + "name: " + value + "\n" + tabSpacing + "}\n";
                    return output;
                }

                std::string getString(){
                    return value;
                }
        };

        class NumberLiteral: ASTNode{
            NodeType type = ASTNode::NumberLiteral;
            int value;

            public:
                NumberLiteral(int _value){
                    value = _value;
                }

                std::string toString(unsigned int tabLevel) override {
                    std::string tabSpacing = std::string(tabLevel * 4, ' ');
                    std::string output = "type: 'NumberLiteral',\n" + tabSpacing + "value: " + std::to_string(value) + "\n" + tabSpacing + "}\n";
                    return output;
                }

                int getValue(){
                    return value;
                }
        };
};