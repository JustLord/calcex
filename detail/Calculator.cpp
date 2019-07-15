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
    if (node->token->getType() == TokenType::Number)
        return node->token->getValue();

    if (node->token->getType() == TokenType::Variable)
    {
        if (auto iter = _variables.find(node->token->getVariable()); iter != _variables.end())
            return iter->second;
        else
            return 0;
    }

    auto lResult = node->token->getOperator() != Operator::Equate ? calculateNode(node->left) : 0;
    auto rResult = calculateNode(node->right);

    switch (node->token->getOperator())
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
        if (node->left->token->getType() == TokenType::Variable)
            _variables[node->left->token->getVariable()] = rResult;
        return rResult;
    }
}

} // namespace detail