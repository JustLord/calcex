#include <iostream>

#include "detail/Calculator.h"
#include "detail/Parser.h"
#include "detail/tokenizer/Tokenizer.h"

using namespace detail;

int main()
{
    char buffer[100];
    Calculator calculator;


    while (true)
    {
        std::cin.getline(buffer, 100);
        auto tokens = Tokenizer(buffer).tokenize();
        auto tree = Parser(tokens).parse();
        calculator.calculate(tree);
        delete tree;
    }

    return 0;
}