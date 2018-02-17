#include <iostream>
#include <vector>
#include <Map>
#include <fstream>
#include "../bin/AST/ASTNode.h"
#include "Handlers/TokenHandler/Tokenizer.h"
#include "Handlers/IOHandler/InputFileHandler.h"
#include "Handlers/IOHandler/OutputFileHandler.h"
#include "Handlers/ParseHandler/Parser.h"

void vistor(ASTNode * astTree);

int main() {
    std::string fileIn = fileToString("..\\Lisp");
    std::vector<Token> out = tokenizer(fileIn);
    ASTNode * outAST = parser(out);
    std::cout << outAST->toString(0);
    vistor(outAST);
    stringToFile("..\\Lisp", outAST->toString(0));
    return 0;
}

void vistor(ASTNode * astTree){
    //TODO: Simplify the Accessing of Children Classes
    //Remove Defensive Programming
    if(astTree->getType() == CallExpression){
        CallExpressionNode * node = (CallExpressionNode *) astTree;
        if(node->getCallee()->getType() == Identifier){
            IdentifierNode * idNode = (IdentifierNode *) node->getCallee();
            if(idNode->getValue() == "set"){

            }
        }
    }

    for(int i = 0; i < astTree->getChildren().size(); i++){
        vistor(astTree->getChildren()[i]);
    }
}