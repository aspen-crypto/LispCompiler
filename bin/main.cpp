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

int getValueNumber(ASTNode *);
bool getValueIsNumber(ASTNode *);
void addConstant(ASTNode *);

void vistor(ASTNode * astTree){
    for(int i = 0; i < astTree->getChildren().size(); i++){
        vistor(astTree->getChildren()[i]);
    }

    if(astTree->getType() == CallExpression){
        CallExpressionNode * node = (CallExpressionNode *) astTree;
        if(node->getCallee()->getType() == Identifier) {
            IdentifierNode *idNode = (IdentifierNode *) node->getCallee();
                if (idNode->getValue() == "setq") {
                    if (node->getChildren()[0]->getType() == Identifier) {
                        IdentifierNode *variableName = (IdentifierNode *) node->getChildren()[0];
                        variables[variableName->getValue()] = node->getChildren()[1];
                    } else {
                        std::cout << "Setting a Variable Requires Name" << std::endl;
                        exit(170);
                    }
                } else if (idNode->getValue() == "add"){
                    addConstant(node->getChildren()[0]);
                    addConstant(node->getChildren()[1]);
                    outputString += "IADD ";
                } else if (idNode->getValue() == "sub"){
                    addConstant(node->getChildren()[0]);
                    addConstant(node->getChildren()[1]);
                    outputString += "ISUB ";
                } else if (idNode->getValue() == "mult"){
                    addConstant(node->getChildren()[0]);
                    addConstant(node->getChildren()[1]);
                    outputString += "IMULT ";
                } else if (idNode->getValue() == "div"){
                    addConstant(node->getChildren()[0]);
                    addConstant(node->getChildren()[1]);
                    outputString += "IDIV ";
                } else if (idNode->getValue() == "print"){
                    outputString += "PRINT";
                } else {
                    std::cout<< "Unknown Call to " + idNode ->getValue();
                    exit(160);
                }
            } else {
            std::cout << "Can't Call /n" + node->getCallee()->toString(0);
        }
    }
}

void addConstant(ASTNode * constantToAdd){
    if(getValueIsNumber(constantToAdd)) {
        int valueOne = getValueNumber(constantToAdd);
        outputString += "ICONST " + std::to_string(valueOne) + " ";
    }
}


int getValueNumber(ASTNode * mainNode) {
    if (mainNode->getType() == Identifier) {
        IdentifierNode *idNodeInner = (IdentifierNode *) mainNode;
        if(variables[idNodeInner->getValue()]->getType() == NumberLiteral) {
            NumberLiteralNode *number = (NumberLiteralNode *) variables[idNodeInner->getValue()];
            return number->getValue();
        } else {
            //TODO: Implement Proper Fancy Variable Handling
            std::cout << "Variable Turned Out Not to be a Number" << std::endl;
        }
    } else if(mainNode->getType() == NumberLiteral) {
            NumberLiteralNode *number = (NumberLiteralNode *) mainNode;
            return number->getValue();
    }
}

bool getValueIsNumber(ASTNode * mainNode) {
    if (mainNode->getType() == Identifier) {
        IdentifierNode *idNodeInner = (IdentifierNode *) mainNode;
        if(variables[idNodeInner->getValue()]->getType() == NumberLiteral) {
            return true;
        }
    } else if (mainNode->getType() == NumberLiteral) {
            return true;
    } else {
        return false;
    }
}