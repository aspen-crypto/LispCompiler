cmake_minimum_required(VERSION 3.9)
project(LispCompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(LispCompiler main.cpp ASTNode.cpp ASTNode.h ASTType.h)