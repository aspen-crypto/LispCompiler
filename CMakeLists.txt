cmake_minimum_required(VERSION 3.9)
project(LispCompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(LispCompiler bin/main.cpp bin/AST/ASTNode.cpp bin/AST/ASTNode.h bin/AST/ASTType.h)