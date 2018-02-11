#ifndef LISPCOMPILER_ASTNODE_H
#define LISPCOMPILER_ASTNODE_H

#include "ASTType.h"

class ASTNode {
    std::vector<ASTNode *> children;
    NodeType type;

    public:
        NodeType getType();
        std::vector<ASTNode *> getChildren();
        virtual std::string toString(unsigned int tabLevel);
        void setChildren(std::vector<ASTNode *> _children);
        void setNodeType(NodeType _type);
};

class ProgramNode : public ASTNode {
    NodeType type;

    public:
        explicit ProgramNode(std::vector<ASTNode *> _body);
        std::string toString(unsigned int tabLevel) override;
};

class ExpressionStatementNode : public ASTNode {
    NodeType type;

    public:
        explicit ExpressionStatementNode(std::vector<ASTNode *> _expression);
        std::string toString(unsigned int tabLevel) override;
};

class CallExpressionNode : public ASTNode {
    NodeType type;
    ASTNode * callee;

    public:
        CallExpressionNode(ASTNode * _callee, std::vector<ASTNode *> _args);
        std::string toString(unsigned int tabLevel) override;
};

class IdentifierNode : public ASTNode {
    NodeType type;
    std::string value;

    public:
        explicit IdentifierNode(std::string _value);
        std::string getValue();
        std::string toString(unsigned int tabLevel) override;
};

class NumberLiteralNode : public ASTNode{
    NodeType type;
    int value;

    public:
        explicit NumberLiteralNode(int _value);
        int getValue();
        std::string toString(unsigned int tabLevel) override;
};

#endif //LISPCOMPILER_ASTNODE_H
