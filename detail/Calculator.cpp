//
// Created by nikita on 7/6/19.
//

#include "Calculator.h"
#include <cmath>
#include <iostream>

namespace detail {
void Calculator::calculate(const TreeNode *root) { std::cout << calculateNode(root) << std::endl; }

double Calculator::calculateNode(const TreeNode *node)
{
    if (node->value.token == TokenType::Number)
        return node->value.value;

    if (node->value.token == TokenType::Variable)
    {
        double *  variable;
        if(auto iterator = _variablesMap.find(node->value.variable); iterator != _variablesMap.end())
        {
            variable = iterator->second;
        }
        else
        {
            variable = new double();
            _variablesMap[node->value.variable]  = variable;
        }

        return *variable;
    }

    auto lResult = node->value._operator != Operator::Equate ? calculateNode(node->left) : 0;
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
        double *  variable;
        if(auto iterator = _variablesMap.find(node->value.variable); iterator != _variablesMap.end())
        {
            variable = iterator->second;
        }
        else
        {
            variable = new double();
            _variablesMap[std::string(node->left->value.variable)]  = variable;
        }

        if (node->left->value.token == TokenType::Variable)
            *variable = rResult;
        return rResult;
    }

    }
}

} // namespace detail