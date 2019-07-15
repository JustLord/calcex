//
// Created by nikita on 7/4/19.
//

#include "Parser.h"
#include <stack>
#include <stdexcept>

namespace detail {

TreeNode *Parser::parse()
{
    for (auto &token : _tokens)
    {
        if (token.getType() == TokenType::Operator)
            parseOperator(token);
        else
            parseOperand(token);
    }

    return _root;
}
void Parser::parseOperand(const Token &token)
{
    auto node = new TreeNode(&token);

    if (!_root)
        _root = node;
    else
        _operators.top()->right = node;
}

void Parser::parseOperator(const Token &token)
{
    switch (token.getOperator())
    {
    case Operator::OpeningBracket:
        parseOpeningBracket(token);
        break;
    case Operator::ClosingBracket:
        parseClosingBracket(token);
        break;
    case Operator::Plus:
    case Operator::Minus:
    case Operator::Multiple:
    case Operator::Divide:
    case Operator ::Equate:
    case Operator::Exponentiation:
        parseArithmetic(token);
        break;
    }
}

void Parser::parseArithmetic(const Token &token)
{
    auto node = new TreeNode(&token);

    if (_root)
    {
        while (!_operators.empty() && OperatorPriority(token.getOperator()) > OperatorPriority(_operators.top()->token->getOperator()))
            _operators.pop();

        if (!_operators.empty())
        {
            node->left = _operators.top()->right;
            _operators.top()->right = node;
        }
        else
        {
            node->left = _root;
            _root = node;
        }
    }

    _operators.push(node);
}
void Parser::parseClosingBracket(const Token &token)
{
    while (!_operators.empty() && _operators.top()->token->getOperator() != Operator::OpeningBracket)
        _operators.pop();

    if (_operators.empty())
        throw std::logic_error("Opening bracket was expected");

    auto bracket = _operators.top();

    _operators.pop();

    if (!_operators.empty())
        _operators.top()->right = bracket->right;
    else
        _root = bracket->right;

	bracket->left = nullptr;
    bracket->right = nullptr;
    delete bracket;
}
void Parser::parseOpeningBracket(const Token &token)
{
    auto node = new TreeNode(&token);
    if (!_operators.empty())
        _operators.top()->right = node;
    else
        _root = node;

    _operators.push(node);
}

} // namespace detail