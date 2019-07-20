//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_PARSER_H
#define CALCEX_PARSER_H

#include "../tokenizer/Token.h"
#include "Tree.h"
#include <memory>
#include <stack>
#include <vector>
#include <map>

namespace detail {

class Parser
{
public:
    Parser(const std::vector<Token> &tokens);

    TreeNode *parse();

private:
    void parseOperand(const Token &token);
    void parseOperator(const Token &token);
    void parseVariable(const Token &token);

    void parseArithmetic(const Token &token);
    void parseClosingBracket(const Token &token);
    void parseOpeningBracket(const Token &token);

private:
    const std::vector<Token> &_tokens;

    TreeNode *_root;
    std::stack<TreeNode *> _operators;
};

inline Parser::Parser(const std::vector<detail::Token> &tokens)
    : _tokens{tokens}, _root{nullptr}
{}

} // namespace detail

#endif //CALCEX_PARSER_H
