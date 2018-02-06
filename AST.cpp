#include "AST.h"
#include <iostream>
#include <vector>

class ASTNode;

class AST {
    ASTNode createNode(){
        return NULL;
    }
};

class ASTNode {
    class Program;
    class BodyNode;

    public:
        enum NodeType {Program, ExpressionStatement, CallExpression, Identifier, NumberLiteral};

        Program createProgram(){

        }

    private:
        class Program{
            std::vector<BodyNode> body;
            NodeType type = ASTNode::Program;

            Program (std::vector<BodyNode> _body) {
                body = _body;
            }
        };

        class BodyNode {
            NodeType type;

            BodyNode(NodeType _type){
                type = _type;
            }
        };
};