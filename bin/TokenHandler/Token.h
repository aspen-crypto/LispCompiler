//
// Created by Spoon on 2/11/2018.
//

#ifndef LISPCOMPILER_TOKEN_H
#define LISPCOMPILER_TOKEN_H

#include "TokenType.h"
#include <iostream>

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


#endif //LISPCOMPILER_TOKEN_H
