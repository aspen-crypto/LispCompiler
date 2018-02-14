#include <iostream>
#include <vector>
#include <fstream>
#include "../bin/AST/ASTNode.h"
#include "Handlers/TokenHandler/Tokenizer.h"
#include "Handlers/IOHandler/InputFileHandler.h"
#include "Handlers/IOHandler/OutputFileHandler.h"
#include "Handlers/ParseHandler/Parser.h"

int main() {
    std::string fileIn = fileToString("..\\Lisp");
    std::vector<Token> out = tokenizer(fileIn);
    ASTNode * outAST = parser(out);
    std::cout << outAST->toString(0);
    stringToFile("..\\Lisp", outAST->toString(0));
    return 0;
}