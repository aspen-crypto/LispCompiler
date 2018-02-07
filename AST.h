//
// Created by Spoon on 2/5/2018.
//

#ifndef LISPCOMPILER_AST_H
#define LISPCOMPILER_AST_H
#include <iostream>
#include <vector>

class ASTNode{
    public:
        virtual std::string toString(unsigned int tabLevel);
};
class ProgramNode : public ASTNode{
    public:
        explicit ProgramNode(std::vector<ASTNode *> _body);
};
class ExpressionStatementNode;
class CallExpressionNode;
class IdentifierNode;
class NumberLiteralNode : public ASTNode{
    public:
        explicit NumberLiteralNode(int value);
};

#endif //LISPCOMPILER_AST_H
