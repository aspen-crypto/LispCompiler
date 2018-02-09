#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>

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
        children = std::move(_children);
    }

    private:
        NodeType type;
};

class ProgramNode : public ASTNode{
    NodeType type = ASTNode::Program;

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
    NodeType type = ASTNode::ExpressionStatement;

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
    NodeType type = ASTNode::CallExpression;
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
    NodeType type = ASTNode::Identifier;
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

enum TokenType {NumberToken, ParenToken, NameToken};

struct Token {
    TokenType type;
    std::string value;

    std::string toString(){
        switch(type){
            case NumberToken:
                return  "TokenType: NumberToken; Value: " + value;
            case ParenToken:
                return  "TokenType: ParenToken; Value: " + value;
            case NameToken:
                return  "TokenType: NameToken; Value: " + value;
            default:
                return "TokenType: NULL; Value: " + value;
        }
    }
};

std::string fileToString(const std::string &fileName);
std::vector<Token> tokenizer(std::string inputCode);

ASTNode * parser(const std::vector<Token> &inputTokens);
ASTNode * walk(int& current, std::vector<Token> inputTokens);


int main() {
    std::string fileIn = fileToString("Lisp");
    std::cout << fileIn << std::endl;
    std::vector<Token> out = tokenizer(fileIn);
    ASTNode * outAST = parser(out);
    std::cout << outAST->toString(0);
    return 0;
}

std::string fileToString(const std::string &fileName){
    std::ifstream t("C:\\Users\\Spoon\\CLionProjects\\LispCompiler\\Lisp.lasp", std::ios::binary);
    std::string out;
    out.assign((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return out;
}

std::vector<Token> tokenizer(std::string inputCode){
    std::vector<Token> tokens;
    for(int i = 0; i <= inputCode.length(); i++){
        if(inputCode[i] == '(' || inputCode[i] == ')'){
            Token currentToken;
            currentToken.type = ParenToken;
            currentToken.value = inputCode[i];
            tokens.push_back(currentToken);
        } else if (isdigit(inputCode[i])) {
            Token currentToken;
            currentToken.type = NumberToken;
            while (isdigit(inputCode[i])) {
                currentToken.value += inputCode[i];
                i++;
            }
            i--;
            tokens.push_back(currentToken);
        } else if (isalpha(inputCode[i])){
            Token currentToken;
            currentToken.type = NameToken;
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

ASTNode * parser (const std::vector<Token> &inputTokens){
    int current = 0;
    int & send = current;

    std::vector<ASTNode * >ASTBody;
    while(current < inputTokens.size()){
        ASTBody.push_back(walk(send, inputTokens));
    }

    return new ProgramNode(ASTBody);
}

ASTNode * walk(int &current, std::vector<Token> inputTokens){
    Token token = inputTokens[current];
    if(current + 1 <= inputTokens.size()) {
        switch (token.type) {
            case NumberToken: {
                if (current + 1 < inputTokens.size()) {
                    current++;
                    return new NumberLiteralNode(std::stoi(token.value));
                } else {
                    std::cout << "Missing Closing Parentheses" << std::endl;
                    exit(150);
                }
            }
            case ParenToken: {
                if (token.value == "(") {
                    current++;
                    token = inputTokens[current];

                    ASTNode *_callee = new IdentifierNode(token.value);

                    if (current + 1 <= inputTokens.size()) {
                        current ++;
                        token = inputTokens[current];
                    } else {
                        std::cout << "Missing Closing Parentheses" << std::endl;
                        exit(150);
                    }

                    std::vector<ASTNode *> _args;
                    while (token.type != ParenToken || token.type == ParenToken && token.value != ")") {
                        _args.push_back(walk(current, inputTokens));
                        token = inputTokens[current];
                    }
                    if(current + 1 <= inputTokens.size()) {
                        current++;
                        return new CallExpressionNode(_callee, _args);
                    } else {
                        std::cout << "Missing Closing Parentheses" << std::endl;
                        exit(150);
                    }
                }
                break;
            }
            case NameToken: {
                if(current <= inputTokens.size()){
                    current++;
                    return new IdentifierNode(token.value);
                }
            }
            default: {
                std::cout << "INVALID Token - " + token.toString();
                exit(110);
            }
        }
    } else {
        std::cout << "Missing Closing Parentheses" << std::endl;
        exit(150);
    }
}