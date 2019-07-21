#include <iostream>

#include "detail/Calculator.h"
#include "detail/parser/Parser.h"
#include "detail/tokenizer/Tokenizer.h"

using namespace detail;

int main()
{
    char buffer[100];
    Calculator calculator;
    Parser parser;

    while (true)
    {
        std::cin.getline(buffer, 100);
        auto tokens = Tokenizer(buffer).tokenize();
        auto tree = parser.parse(tokens);
        calculator.calculate(tree);
        delete tree;
    }

    return 0;
}