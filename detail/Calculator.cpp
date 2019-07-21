//
// Created by nikita on 7/6/19.
//

#include "Calculator.h"
#include <cmath>
#include <iostream>

namespace detail {
void Calculator::calculate(const TreeNode *root)
{
    calculateNode(root);
}

double Calculator::calculateNode(const TreeNode *node)
{
    if (node->value.token == TokenType::Number)
        return node->value.value;

    if (node->value.token == TokenType::Symbol)
        return *node->value.variable;

    auto lResult = node->value._operator != Operator::Equate && node->value._operator != Operator::Print  ? calculateNode(node->left) : 0;
    auto rResult = calculateNode(node->right);

    switch (node->value._operator)
    {
    case Operator::Plus:
        return lResult + rResult;
    case Operator::Minus:
        return lResult - rResult;
    case Operator::Multiple:
        return lResult * rResult;
    case Operator::Divide:
        return lResult / rResult;
    case Operator::Exponentiation:
        return pow(lResult, rResult);
    case Operator::OpeningBracket:
    case Operator::ClosingBracket:
        return 0;
    case Operator::Equate:
    {
        if (node->left->value.token == TokenType::Symbol)
            *node->left->value.variable = rResult;

        return rResult;
    }
    case Operator::Print:
        std::cout << rResult << std::endl;
        return 0;
    }
}

} // namespace detail