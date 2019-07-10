//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_PARSER_H
#define CALCEX_PARSER_H

#include "tokenizer/Token.h"
#include <stack>
#include <vector>

namespace detail {

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;

    const Token *token;

    TreeNode(const Token *d);
};

inline TreeNode::TreeNode(const detail::Token *d)
    : token{d}, left{}, right{}
{}

class Parser
{
public:
    Parser(const std::vector<Token> &tokens);

    TreeNode *parse();

private:
    void parseOperand(const Token &token);
    void parseOperator(const Token &token);
    void parseArithmetic(const Token &token);
    void parseClosingBracket(const Token &token);
    void parseOpeningBracket(const Token &token);

private:
    const std::vector<Token> &_tokens;

    TreeNode *_root;
    std::stack<TreeNode *> _operators;
    std::stack<TreeNode *> _operands;
};

inline Parser::Parser(const std::vector<detail::Token> &tokens)
    : _tokens{tokens}, _root{nullptr}
{}

} // namespace detail

#endif //CALCEX_PARSER_H
