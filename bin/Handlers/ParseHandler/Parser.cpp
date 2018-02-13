#include "Parser.h"

ASTNode * parser (const std::vector<Token> &inputTokens){
    int current = 0;
    int & send = current;

    std::vector<ASTNode * >ASTBody;
    while(current < inputTokens.size()){
        ASTBody.push_back(walk(send, inputTokens));
    }

    return new ProgramNode(ASTBody);
}

ASTNode * walk(int &current, std::vector<Token> inputTokens) {
    Token token = inputTokens[current];
    if (current + 1 <= inputTokens.size()) {
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
                        current++;
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
                    if (current + 1 <= inputTokens.size()) {
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
                if (current <= inputTokens.size()) {
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