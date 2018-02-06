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

        virtual void print(int tabLevel);

    private:
        class Program : ASTNode{
            NodeType type = ASTNode::Program;
            std::vector<ASTNode *> body;

            public :
                Program(std::vector<ASTNode *> _body){
                    type = ASTNode::Program;
                    body = _body;
                }

                void print(int tabLevel) override {
                    tabLevel = 0;
                    for (auto child : body){
                        child->print(tabLevel ++);
                    }
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

                void print(int tabLevel) override {
                    for(auto expression : expressions){
                        expression -> print(tabLevel++);
                    }
                }

                NodeType getType() override {
                    return type;
                }
        };

        class CallExpression : ASTNode{
            NodeType type = ASTNode::CallExpression;
            ASTNode * callee;
            std::vector<ASTNode *> args;

            CallExpression(ASTNode * _callee, std::vector<ASTNode *> _args) {
                callee = _callee;
                args = _args;
            }

            void print(int tabLevel) override {

            }
        };
};