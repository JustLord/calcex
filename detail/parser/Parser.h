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
    TreeNode *parse(const std::vector<Token> &tokens);

private:
    void parseOperand(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators);
    void parseOperator(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators);
    void parseSymbol(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators);

    void parseArithmetic(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators);
    void parseClosingBracket(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators);
    void parseOpeningBracket(const Token &token, TreeNode **root, std::stack<TreeNode *> &operators);

    double * getOrCreateSymbol(const char * name);
private:
    std::map<std::string, double*> _symbols;
};

} // namespace detail

#endif //CALCEX_PARSER_H
