//
// Created by nikita on 7/6/19.
//

#include "Calculator.h"
#include <cmath>
#include <iostream>

namespace detail {
void Calculator::calculate() const { std::cout << calculateNode(_root); }

double Calculator::calculateNode(const TreeNode *node) const
{
    if (node->token->getType() == TokenType::Number)
        return node->token->getNumber();

    auto lResult = calculateNode(node->left);
    auto rResult = calculateNode(node->right);

    switch (node->token->getOperator().type)
    {
    case OperatorType::Plus:
        return lResult + rResult;
    case OperatorType::Minus:
        return lResult - rResult;
    case OperatorType::Multiple:
        return lResult * rResult;
    case OperatorType::Divide:
        return lResult / rResult;
    case OperatorType::Exponentiation:
        return pow(lResult, rResult);
    }
}

} // namespace detail