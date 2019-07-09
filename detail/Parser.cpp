//
// Created by nikita on 7/4/19.
//

#include <stdexcept>
#include "Parser.h"
#include <stdexcept>
#include <stack>

namespace detail {

    TreeNode *Parser::parse() const
    {
        TreeNode *root = nullptr;

        std::stack<TreeNode *> operatorsStack;
        std::stack<TreeNode *> operandsStack;

        for (auto &token : _tokens) {
            auto node = new TreeNode(&token);

            if (!root) {
                if (token.getType() == TokenType::Operator)
                    throw std::logic_error("Operand was expected");

                root = node;
                continue;
            }

            if (root->token->getType() != TokenType::Operator) {
                if (token.getType() != TokenType::Operator)
                    throw std::logic_error("Operator was expected");

                node->left = root;
                root = node;

                operatorsStack.push(node);
                continue;
            }

            if (token.getType() != TokenType::Operator) {
                if (operatorsStack.top()->right)
                    throw std::logic_error("Operator was expected");

                operatorsStack.top()->right = node;

                continue;
            }

            if (token.getType() == TokenType::Operator) {
                while (token.getOperator().priority < operatorsStack.top()->token->getOperator().priority &&
                       !operatorsStack.empty()) {
                    operatorsStack.pop();
                }

                if (!operatorsStack.empty()) {
                    node->left = operatorsStack.top()->right;
                    operatorsStack.top()->right = node;
                } else {
                    node->left = root;
                    root = node;
                }

                operatorsStack.push(node);
            }
        }
        return root;
    }

}