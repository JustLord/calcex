//
// Created by nikita on 7/4/19.
//

#include "Parser.h"
#include "Tree.h"
#include <stack>
#include <stdexcept>

namespace detail {

TreeNode *Parser::parse(const std::vector<Token> &tokens)
{
    TreeNode *root = nullptr;
    std::stack<TreeNode *> operators;

    for (auto &token : tokens)
    {
        if (token.getType() == TokenType::Operator)
            parseOperator(token, &root, operators);
        else if (token.getType() == TokenType::Symbol)
            parseSymbol(token, &root, operators);
        else
            parseOperand(token, &root, operators);
    }

    return root;
}
void Parser::parseOperand(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators)
{
    auto node = new TreeNode(TreeItem(token.getValue()));

    if (!*root)
        *root = node;
    else
        operators.top()->right = node;
}

void Parser::parseOperator(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators)
{
    switch (token.getOperator())
    {
    case Operator::OpeningBracket:
        parseOpeningBracket(token, root, operators);
        break;
    case Operator::ClosingBracket:
        parseClosingBracket(token, root, operators);
        break;
    case Operator::Plus:
    case Operator::Minus:
    case Operator::Multiple:
    case Operator::Divide:
    case Operator::Equate:
    case Operator::Exponentiation:
    case Operator::Print:
        parseArithmetic(token, root, operators);
        break;
    }
}

void Parser::parseArithmetic(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators)
{
    auto node = new TreeNode(TreeItem(token.getOperator()));

    if (*root)
    {
        while (!operators.empty() && OperatorPriority(token.getOperator()) > OperatorPriority(operators.top()->value._operator))
            operators.pop();

        if (!operators.empty())
        {
            node->left = operators.top()->right;
            operators.top()->right = node;
        }
        else
        {
            node->left = *root;
            *root = node;
        }
    }
    else if(token.getOperator() == Operator::Print)
        *root = node;

    operators.push(node);
}
void Parser::parseClosingBracket(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators)
{
    while (!operators.empty() && operators.top()->value._operator != Operator::OpeningBracket)
        operators.pop();

    if (operators.empty())
        throw std::logic_error("Opening bracket was expected");

    auto bracket = operators.top();

    operators.pop();

    if (!operators.empty())
        operators.top()->right = bracket->right;
    else
        *root = bracket->right;

    bracket->left = nullptr;
    bracket->right = nullptr;
    delete bracket;
}
void Parser::parseOpeningBracket(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators)
{
    auto node = new TreeNode(TreeItem(token.getOperator()));
    if (!operators.empty())
        operators.top()->right = node;
    else
        *root = node;

    operators.push(node);
}
void Parser::parseSymbol(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators)
{
    auto node = new TreeNode(TreeItem(getOrCreateSymbol(token.getVariable())));

    if (!*root)
        *root = node;
    else
        operators.top()->right = node;
}
double *Parser::getOrCreateSymbol(const char *name)
{
    if (auto iterator = _symbols.find(name); iterator != _symbols.end())
        return iterator->second;

    auto symbol = new double();
    _symbols[name] = symbol;
    return _symbols[name] = symbol;
}

} // namespace detail