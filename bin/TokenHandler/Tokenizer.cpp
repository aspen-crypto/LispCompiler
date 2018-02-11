//
// Created by Spoon on 2/11/2018.
//

#include "Tokenizer.h"

std::vector<Token> tokenizer(std::string inputCode) {
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
