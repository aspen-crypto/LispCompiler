//
// Created by Spoon on 2/12/2018.
//

#ifndef LISPCOMPILER_PARSER_H
#define LISPCOMPILER_PARSER_H

#include <vector>
#include "../TokenHandler/Token.h"
#include "../../AST/ASTNode.h"

ASTNode * parser (const std::vector<Token> &inputTokens);
ASTNode * walk(int &current, std::vector<Token> inputTokens);


#endif //LISPCOMPILER_PARSER_H
