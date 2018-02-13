cmake_minimum_required(VERSION 3.9)
project(LispCompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(LispCompiler bin/main.cpp bin/AST/ASTNode.cpp bin/AST/ASTNode.h bin/AST/ASTType.h bin/Handlers/TokenHandler/TokenType.h bin/Handlers/TokenHandler/Token.h bin/Handlers/TokenHandler/Tokenizer.cpp bin/Handlers/TokenHandler/Tokenizer.h bin/Handlers/InputHandler/InputFileHandler.cpp bin/Handlers/InputHandler/InputFileHandler.h bin/Handlers/ParseHandler/Parser.cpp bin/Handlers/ParseHandler/Parser.h)