//
// Created by nikita on 7/4/19.
//

#include <stdexcept>
#include "Parser.h"
#include <stdexcept>


namespace detail
{

    TreeNode * Parser::parse() const {
        TreeNode *root = nullptr;
        TreeNode *prev = nullptr;

        for(auto & token : _tokens)
        {
            if (!root)
            {
                root = prev = new TreeNode{&token};
                continue;
            }

            if(root->token->getType() != TokenType::Operator)
            {
                if(token.getType()!=TokenType::Operator)
                    throw std::logic_error("Operator was expected");

                auto node = new TreeNode(&token);
                node->left = prev;
                root = prev = node;
                node->left->parent = node;
                continue;
            }

            if(prev->token->getType() == TokenType::Operator)
            {
                if(token.getType()==TokenType::Operator)
                    throw std::logic_error("Operand was expected");

                auto node = new TreeNode(&token);
                node->parent = prev;
                prev->right = node;
                prev = node;
                continue;
            }

            if(prev->token->getType() != TokenType::Operator)
            {
                if(token.getType()!=TokenType::Operator)
                    throw std::logic_error("Operator was expected");


                auto &_node = prev;

                if(_node->parent->token->getOperator().priority > token.getOperator().priority)
                {
                    while(_node->parent)
                    {
                        if(_node->parent->token->getType() == TokenType::Operator)
                            if(_node->parent->token->getOperator().priority <= token.getOperator().priority)
                                break;

                         _node = _node->parent;
                    }
                }


                if(_node->parent->token->getOperator().priority > token.getOperator().priority)
                {
                    auto node = new TreeNode(&token);
                    node->left = _node->parent;
                    node->left->parent = node;
                    root = prev = node;
                    continue;

                }

                auto node = new TreeNode(&token);
                node->parent = _node->parent;
                node->left = _node;
                node->left->parent = node;

                prev = node;
                continue;
            }
        }

        return root;
    }
}