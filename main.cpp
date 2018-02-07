#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

class ASTNode {
    std::vector<ASTNode *> children;

public:
    enum NodeType {Program, ExpressionStatement, CallExpression, Identifier, NumberLiteral};

    NodeType getType(){
        return type;
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
        children = _children;
    }

    private:
        NodeType type;
};

class ProgramNode : public ASTNode{
    NodeType type = ASTNode::Program;

public :
    explicit ProgramNode(std::vector<ASTNode *> _body){
        setChildren(_body);
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
    NodeType type = ASTNode::ExpressionStatement;

public :
    explicit ExpressionStatementNode(std::vector<ASTNode *> _expressions){
        setChildren(_expressions);
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
    NodeType type = ASTNode::CallExpression;
    ASTNode * callee;

public:
    CallExpressionNode(ASTNode * _callee, std::vector<ASTNode *> _args) {
        callee = _callee;
        setChildren(_args);
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
    NodeType type = ASTNode::Identifier;
    std::string value;

public:
    explicit IdentifierNode(std::string _value){
        value = _value;
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
    NodeType type = ASTNode::NumberLiteral;
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

//class AST {
//public :
//    enum ASTTypes {
//        Program, ExpressionStatement, CallExpression, Identifier, NumberLiteral
//    };
//    ASTTypes type;
//    std::vector<AST *> body;
//    AST* callee;
//    std::vector<AST *> args;
//    std::string value;
//
//    AST(ASTTypes _type, std::vector<AST *> _body) {
//        if (_type == Program || type == ExpressionStatement) {
//            type = _type;
//            body = _body;
//        } else {
//            std::cout << "Invalid Type " + typeToString(_type) + " can't be declared with a body" << std::endl;
//            exit(100);
//        }
//    }
//
//    AST(ASTTypes _type, AST * _callee, std::vector<AST *> _args) {
//        if (_type == CallExpression) {
//            type = _type;
//            callee = _callee;
//            args = _args;
//        } else {
//            std::cout << "Invalid Type " + typeToString(_type) + " can't be declared with a Callee and Args"
//                      << std::endl;
//            exit(100);
//        }
//    }
//
//    AST(ASTTypes _type, std::string _value) {
//        if (_type == Identifier || _type == NumberLiteral) {
//            type = _type;
//            value = _value;
//        } else {
//            std::cout << "Invalid Type " + typeToString(_type) + " can't be declared with a value" << std::endl;
//            exit(100);
//        }
//    }
//
//    std::string getValue() {
//        if (type == NumberLiteral || type == Identifier) {
//            return value;
//        } else {
//            std::cout << "Type " + typeToString(type) + " doesn't have a value" << std::endl;
//            exit(105);
//        }
//    }
//
//    std::vector<AST *> getBody() {
//        if (type == Program) {
//            return body;
//        } else {
//            std::cout << "Type " + typeToString(type) + " doesn't have a value" << std::endl;
//            exit(105);
//        }
//    }
//
//    AST * getCallee() {
//        if (type == CallExpression) {
//            return callee;
//        } else {
//            std::cout << "Type " + typeToString(type) + " doesn't have a callee" << std::endl;
//            exit(105);
//        }
//    }
//
//    std::vector<AST *> getArguments() {
//        if (type == CallExpression) {
//            return args;
//        } else {
//            std::cout << "Type " + typeToString(type) + " doesn't have Arguments" << std::endl;
//            exit(105);
//        }
//    }
//
//    std::string toString() {
//        switch (type) {
//            case Program: {
//                std::string programOut = "type: 'Program', \nbody: [{\n";
//                for (auto &i : body) {
//                    programOut += i->toString();
//                }
//                programOut += "}]";
//                return programOut;
//            }
//            case ExpressionStatement: {
//                std::string expressionOut = "  type: 'ExpressionStatement',\n  expression: {\n";
//                for (auto &i : body) {
//                    expressionOut += i->toString();
//                }
//                expressionOut += "}\n";
//                return expressionOut;
//                }
//            case CallExpression: {
//                std::string callExpressionOut =
//                        "  type: 'CallExpression',\n  callee: {\n    " + callee->toString() + "args: {";
//                for(auto &i : args){
//                    callExpressionOut += i->toString();
//                }
//                callExpressionOut += "}";
//                return callExpressionOut;
//            }
//            case Identifier: {
//                std::string identifierOut = "  type: 'Identifier',\n      name: " + value + "   \n  }\n    ";
//                return identifierOut;
//            }
//            case NumberLiteral: {
//                std::string numberOut = "  type: 'NumberLiteral',\n      value: " + value + "   \n  }\n    ";
//                return numberOut;
//            }
//            default: {
//                return "MALFORMED AST";
//            }
//
//        }
//    }
//
//
//private:
//    std::string typeToString(ASTTypes _type) {
//        switch (_type) {
//            case Program:
//                return "Program";
//            case ExpressionStatement:
//                return "ExpressionStatement";
//            case CallExpression:
//                return "CallExpression";
//            case Identifier:
//                return "Identifier";
//            case NumberLiteral:
//                return "NumberLiteral";
//            default: return "[INVALID TYPE]";
//        }
//    }
//
//
//};

struct Token {
    std::string type;
    std::string value;

    std::string toString(){
        return "Type: " + type + "; Value: " + value;
    }
};


std::vector<Token> tokenizer(std::string inputCode);

ASTNode * parser(std::vector<Token> inputTokens);
ASTNode * walk(int& current, std::vector<Token> inputTokens);


int main() {
    std::string testing = "(add 500 (subtract 23))(Testing 203)";
    std::vector<Token> out = tokenizer(testing);
    ASTNode * outAST = parser(out);
    std::cout << outAST->toString(0);
    return 0;
}

std::vector<Token> tokenizer(std::string inputCode){
    std::vector<Token> tokens;
    for(int i = 0; i <= inputCode.length(); i++){
        if(inputCode[i] == '(' || inputCode[i] == ')'){
            Token currentToken;
            currentToken.type = "paren";
            currentToken.value = inputCode[i];
            tokens.push_back(currentToken);
        } else if (isdigit(inputCode[i])) {
            Token currentToken;
            currentToken.type = "number";
            while (isdigit(inputCode[i])) {
                currentToken.value += inputCode[i];
                i++;
            }
            i--;
            tokens.push_back(currentToken);
        } else if (isalpha(inputCode[i])){
            Token currentToken;
            currentToken.type = "name";
            while(isalpha(inputCode[i])) {
                currentToken.value += inputCode[i];
                i++;
            }
            i--;
            tokens.push_back(currentToken);
        }
    }
    return tokens;
}

ASTNode * parser (std::vector<Token> inputTokens){
    int current = 0;
    int & send = current;

    std::vector<ASTNode * >ASTBody;
    while(current < inputTokens.size()){
        ASTBody.push_back(walk(send, inputTokens));
    }

    return new ProgramNode(ASTBody);
}

ASTNode * walk(int& current, std::vector<Token> inputTokens){
    Token token = inputTokens[current];
    if(token.type == "number"){
        current++;
        return new NumberLiteralNode(std::stoi(token.value));
    }
    if(token.type == "paren" && token.value == "(") {
        current++;
        token = inputTokens[current];

        ASTNode *_callee = new IdentifierNode(token.value);
        current++;
        token = inputTokens[current];
        std::vector<ASTNode *> _args;
        while (token.type != "paren" || (token.type == "paren" && token.value != ")")) {
            _args.push_back(walk(current, inputTokens));
            token = inputTokens[current];
        }
        current++;
        return new CallExpressionNode(_callee, _args);
    }
    if(token.type == "name") {
        current++;
        return new IdentifierNode(token.value);
    }
    if(token.type != "number" || token.type != "paren") {
        std::cout << "INVALID Token Type " + token.type + "; Value " + token.value;
        exit(110);
    }
}
