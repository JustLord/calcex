//
// Created by nikita on 7/4/19.
//

#ifndef CALCEX_PARSER_H
#define CALCEX_PARSER_H


#include <vector>
#include "Token.h"

namespace detail {
    struct TreeNode
    {
        TreeNode *left;
        TreeNode *right;

        const Token *token;

        TreeNode(const Token *d);
    };

    inline TreeNode::TreeNode(const detail::Token *d) :token{d}, left{}, right{} {}


    class Parser {
    public:
        Parser(const std::vector<Token> &tokens);

        TreeNode * parse() const;

    private:
        const std::vector<Token> &_tokens;
    };

    inline Parser::Parser(const std::vector<detail::Token> &tokens) :_tokens{tokens} {}

}



#endif //CALCEX_PARSER_H
