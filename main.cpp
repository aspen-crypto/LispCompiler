#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>
#include "ASTNode.h"

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
    std::string fileIn = fileToString("C:\\Users\\Spoon\\CLionProjects\\LispCompiler\\Lisp");
    std::cout << fileIn << std::endl;
    std::vector<Token> out = tokenizer(fileIn);
    ASTNode * outAST = parser(out);
    std::cout << outAST->toString(0);
    return 0;
}

std::string fileToString(const std::string &fileName){
    std::ifstream t(fileName + ".lasp", std::ios::binary);
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

void vistor(std::vector<ASTNode *> programToRun){

}