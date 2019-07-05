cmake_minimum_required(VERSION 3.14)
project(calcex)

set(CMAKE_CXX_STANDARD 17)

add_executable(calcex main.cpp detail/Tokenizer.h detail/Token.h detail/Tokenizer.cpp detail/Parser.cpp detail/Parser.h)