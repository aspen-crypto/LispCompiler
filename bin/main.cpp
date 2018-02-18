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
std::map<std::string, ASTNode *> variables;

std::string outputString;

int main() {
    std::string fileIn = fileToString("..\\Lisp");
    std::vector<Token> out = tokenizer(fileIn);
    ASTNode * outAST = parser(out);
    std::cout << outAST->toString(0);
    vistor(outAST);
    stringToFile("..\\Lisp", outputString);
    return 0;
}

void vistor(ASTNode * astTree){
    if(astTree->getType() == CallExpression){
        CallExpressionNode * node = (CallExpressionNode *) astTree;
        if(node->getCallee()->getType() == Identifier) {
            IdentifierNode *idNode = (IdentifierNode *) node->getCallee();
                if (idNode->getValue() == "set") {
                    if (node->getChildren()[0]->getType() == Identifier) {
                        IdentifierNode *variableName = (IdentifierNode *) node->getChildren()[0];
                        variables[variableName->getValue()] = node->getChildren()[1];
                    }
                } else if (idNode->getValue() == "add"){
                    int valueOne = 0;
                    int valueTwo = 0;
                    if (node->getChildren()[0]->getType() == Identifier) {
                        IdentifierNode *idNodeInner = (IdentifierNode *) node->getChildren()[0];
                        if(variables[idNodeInner->getValue()]->getType() == NumberLiteral) {
                            NumberLiteralNode *number = (NumberLiteralNode *) variables[idNodeInner->getValue()];
                            valueOne = number->getValue();
                        }
                    } else {
                        if(node->getChildren()[0]->getType() == NumberLiteral) {
                            NumberLiteralNode *number = (NumberLiteralNode *) node->getChildren()[0];
                            valueOne = number->getValue();
                        }
                    }

                    if (node->getChildren()[1]->getType() == Identifier) {
                        IdentifierNode *idNodeInner = (IdentifierNode *) node->getChildren()[1];
                        if(variables[idNodeInner->getValue()]->getType() == NumberLiteral) {
                            NumberLiteralNode *number = (NumberLiteralNode *) variables[idNodeInner->getValue()];
                            valueTwo = number->getValue();
                        }
                    } else {
                        if(node->getChildren()[1]->getType() == NumberLiteral) {
                            NumberLiteralNode *number = (NumberLiteralNode *) node->getChildren()[1];
                            valueTwo = number->getValue();
                        }
                    }


                    outputString += "IADD " + std::to_string(valueOne) + " " + std::to_string(valueTwo) + "\n";
                }
            } else {
            std::cout << "Can't Call /n" + node->getCallee()->toString(0);
        }
    }

    for(int i = 0; i < astTree->getChildren().size(); i++){
        vistor(astTree->getChildren()[i]);
    }
}