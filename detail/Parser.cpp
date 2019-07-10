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
        _operands.push(node);
    else
        _operators.top()->right = node;
}

void Parser::parseOperator(const Token &token)
{
    switch (token.getOperator().type)
    {
    case OperatorType::OpeningBracket:
        parseOpeningBracket(token);
        break;
    case OperatorType::ClosingBracket:
        parseClosingBracket(token);
        break;
    case OperatorType::Plus:
    case OperatorType::Minus:
    case OperatorType::Multiple:
    case OperatorType::Divide:
    case OperatorType::Exponentiation:
        parseArithmetic(token);
        break;
    }
}

void Parser::parseArithmetic(const Token &token)
{
    auto node = new TreeNode(&token);

    if (_root)
    {
        while (!_operators.empty() && token.getOperator().priority < _operators.top()->token->getOperator().priority)
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
    else if (!_operands.empty())
    {
        node->left = _operands.top();
        _operands.pop();
        _root = node;
    }

    _operators.push(node);
}
void Parser::parseClosingBracket(const Token &token)
{
    while (!_operators.empty() && _operators.top()->token->getOperator().type != OperatorType::OpeningBracket)
        _operators.pop();

    if (_operators.empty())
        throw std::logic_error("Opening bracket was expected");

    auto bracket = _operators.top();

    _operators.pop();

    if (!_operators.empty())
        _operators.top()->right = bracket->right;
    else
        _root = bracket->right;

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