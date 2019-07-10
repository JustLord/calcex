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

        for (auto &token : _tokens)
        {
            auto node = new TreeNode(&token);

            if (token.getType() != TokenType::Operator)
            {
                if (operatorsStack.empty())
                {
                    operandsStack.push(node);
                } else
                {
                    ((TreeNode *) operatorsStack.top())->right = node;
                }

                continue;
            }

            if (token.getType() == TokenType::Operator)
            {
                if (!root)
                {
                    operatorsStack.push(node);
                    root = node;
                    continue;
                }

                if (token.getOperator().type == OperatorType::OpeningBracket)
                {
                    operatorsStack.top()->right = node;
                    operatorsStack.push(node);

                    continue;
                }

                if (!operandsStack.empty())
                {
                    node->left = operandsStack.top();
                    operandsStack.pop();
                }

                if (token.getOperator().type == OperatorType::ClossingBracket)
                {
                    while (!operatorsStack.empty() && ((TreeNode *) operatorsStack.top())->token->getOperator().type !=
                                                      OperatorType::OpeningBracket)
                        operatorsStack.pop();

                    if (operatorsStack.empty())
                        throw std::logic_error("Opening bracket was expected");

                    auto bracket = operatorsStack.top();

                    operatorsStack.pop();

                    if (!operatorsStack.empty())
                        ((TreeNode *) operatorsStack.top())->right = bracket->right;
                    else
                        root = bracket->right;

                    delete bracket;
                    delete node;

                    continue;
                }

                while (!operatorsStack.empty() && token.getOperator().priority < operatorsStack.top()->token->getOperator().priority)
                {
                    operatorsStack.pop();
                }

                if (!operatorsStack.empty())
                {
                    node->left = operatorsStack.top()->right;
                    operatorsStack.top()->right = node;
                } else
                {
                    node->left = root;
                    root = node;
                }

                operatorsStack.push(node);
            }
        }
        return root;
    }

}