#include <iostream>
#include <vector>

class AST {
public :
    enum ASTTypes {
        Program, ExpressionStatement, CallExpression, Identifier, NumberLiteral
    };
    ASTTypes type;
    std::vector<AST *> body;
    AST* callee;
    std::vector<AST *> args;
    std::string value;

    AST(ASTTypes _type, std::vector<AST *> _body) {
        if (_type == Program || type == ExpressionStatement) {
            type = _type;
            body = _body;
        } else {
            std::cout << "Invalid Type " + typeToString(_type) + " can't be declared with a body" << std::endl;
            exit(100);
        }
    }

    AST(ASTTypes _type, AST * _callee, std::vector<AST *> _args) {
        if (_type == CallExpression) {
            type = _type;
            callee = _callee;
            args = _args;
        } else {
            std::cout << "Invalid Type " + typeToString(_type) + " can't be declared with a Callee and Args"
                      << std::endl;
            exit(100);
        }
    }

    AST(ASTTypes _type, std::string _value) {
        if (_type == Identifier || _type == NumberLiteral) {
            type = _type;
            value = _value;
        } else {
            std::cout << "Invalid Type " + typeToString(_type) + " can't be declared with a value" << std::endl;
            exit(100);
        }
    }

    std::string getValue() {
        if (type == NumberLiteral || type == Identifier) {
            return value;
        } else {
            std::cout << "Type " + typeToString(type) + " doesn't have a value" << std::endl;
            exit(105);
        }
    }

    std::vector<AST *> getBody() {
        if (type == Program) {
            return body;
        } else {
            std::cout << "Type " + typeToString(type) + " doesn't have a value" << std::endl;
            exit(105);
        }
    }

    AST * getCallee() {
        if (type == CallExpression) {
            return callee;
        } else {
            std::cout << "Type " + typeToString(type) + " doesn't have a callee" << std::endl;
            exit(105);
        }
    }

    std::vector<AST *> getArguments() {
        if (type == CallExpression) {
            return args;
        } else {
            std::cout << "Type " + typeToString(type) + " doesn't have Arguments" << std::endl;
            exit(105);
        }
    }

    std::string toString() {
        switch (type) {
            case Program: {
                std::string programOut = "type: 'Program', \nbody: [{\n";
                for (auto &i : body) {
                    programOut += i->toString();
                }
                programOut += "}]";
                return programOut;
            }
            case ExpressionStatement: {
                std::string expressionOut = "  type: 'ExpressionStatement',\n  expression: {\n";
                for (auto &i : body) {
                    expressionOut += i->toString();
                }
                expressionOut += "}\n";
                return expressionOut;
                }
            case CallExpression: {
                std::string callExpressionOut =
                        "  type: 'CallExpression',\n  callee: {\n    " + callee->toString() + "args: {";
                for(auto &i : args){
                    callExpressionOut += i->toString();
                }
                callExpressionOut += "}";
                return callExpressionOut;
            }
            case Identifier: {
                std::string identifierOut = "  type: 'Identifier',\n      name: " + value + "   \n  }\n    ";
                return identifierOut;
            }
            case NumberLiteral: {
                std::string numberOut = "  type: 'NumberLiteral',\n      value: " + value + "   \n  }\n    ";
                return numberOut;
            }
            default: {
                return "MALFORMED AST";
            }

        }
    }


private:
    std::string typeToString(ASTTypes _type) {
        switch (_type) {
            case Program:
                return "Program";
            case ExpressionStatement:
                return "ExpressionStatement";
            case CallExpression:
                return "CallExpression";
            case Identifier:
                return "Identifier";
            case NumberLiteral:
                return "NumberLiteral";
            default: return "[INVALID TYPE]";
        }
    }


};

struct Token {
    std::string type;
    std::string value;

    std::string toString(){
        return "Type: " + type + "; Value: " + value;
    }
};


std::vector<Token> tokenizer(std::string inputCode);
AST * parser(std::vector<Token> inputTokens);
AST * walk(int& current, std::vector<Token> inputTokens);

//Handles Memory Dealloc
std::vector<AST *> ASTtoDelete;


int main() {
    std::string testing = "(add 450 (subtract 60 20)) (testing 550)";
    std::vector<Token> out = tokenizer(testing);
    AST * outAST = parser(out);
    std::cout << outAST->toString();
    for(auto &i : ASTtoDelete){
        delete(i);
    }
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

AST * parser (std::vector<Token> inputTokens){
    int current = 0;
    int & send = current;

    std::vector<AST * > ASTBody;
    while(current < inputTokens.size()){
        ASTBody.push_back(walk(send, inputTokens));
    }

    AST * _temp =  new AST(AST::Program, ASTBody);
    ASTtoDelete.push_back(_temp);
    return _temp;
}

AST * walk(int& current, std::vector<Token> inputTokens){
    Token token = inputTokens[current];
    if(token.type == "number"){
        current++;
        return new AST(AST::NumberLiteral, token.value);
    }
    if(token.type == "paren" && token.value == "(") {
        current++;
        token = inputTokens[current];

        AST * _temp = new AST(AST::Identifier, token.value);
        ASTtoDelete.push_back(_temp);
        AST *value = _temp;
        current++;
        token = inputTokens[current];
        std::vector<AST *> node;
        while (token.type != "paren" || (token.type == "paren" && token.value != ")")) {
            node.push_back(walk(current, inputTokens));
            token = inputTokens[current];
        }
        current++;
        _temp = new AST(AST::CallExpression, value, node);
        ASTtoDelete.push_back(_temp);
        return _temp;
    }
    if(token.type == "name") {
        current++;
        AST * _temp = new AST(AST::Identifier, token.value);
        ASTtoDelete.push_back(_temp);
        return _temp;
    }
    if(token.type != "number" || token.type != "paren") {
        std::cout << "INVALID Token Type " + token.type + "; Value " + token.value;
        exit(110);
    }
}
