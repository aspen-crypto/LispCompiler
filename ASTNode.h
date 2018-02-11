#ifndef LISPCOMPILER_ASTNODE_H
#define LISPCOMPILER_ASTNODE_H

#include "ASTType.h"

class ASTNode {
    std::vector<ASTNode *> children;

    public:
        NodeType getType();
        std::vector<ASTNode *> getChildren();
        std::string toString();

    private:
        virtual std::string toString(unsigned int tabLevel);
        void setChildren(std::vector<ASTNode *> _children);

};

class ProgramNode : public ASTNode {
    NodeType type;

    public:
        explicit ProgramNode(std::vector<ASTNode *> _body);

    private:
        std::string toString(unsigned int tabLevel) override;
};

class ExpressionStatementNode : public ASTNode {
    NodeType type;

    public:
        explicit ExpressionStatementNode(std::vector<ASTNode *> _expression);

    private:
        std::string toString(unsigned int tabLevel) override;
};

class CallExpressionNode : public ASTNode {
    NodeType type;
    ASTNode * callee;

    public:
        CallExpressionNode(ASTNode * _callee, std::vector<ASTNode *> _args);

    private:
        std::string toString(unsigned int tabLevel) override;
};

class IdentifierNode : public ASTNode {
    NodeType type;
    std::string value;

    public:
        explicit IdentifierNode(std::string _value);
        std::string getValue();

    private:
        std::string toString(unsigned int tabLevel) override;
};

class NumberLiteralNode : public ASTNode{
    NodeType type;
    int value;

    public:
        explicit NumberLiteralNode(int _value);
        int getValue();

    private:
        std::string toString(unsigned int tabLevel) override;
};

#endif //LISPCOMPILER_ASTNODE_H
