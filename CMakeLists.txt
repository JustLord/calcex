cmake_minimum_required(VERSION 3.14)
project(calcex)

set(CMAKE_CXX_STANDARD 17)

add_executable(calcex main.cpp detail/tokenizer/Token.h detail/parser/Parser.cpp detail/parser/Parser.h detail/parser/Tree.h detail/Calculator.cpp detail/Calculator.h detail/tokenizer/Tokenizer.cpp detail/tokenizer/Tokenizer.h)