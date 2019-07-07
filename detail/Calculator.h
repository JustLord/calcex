//
// Created by nikita on 7/6/19.
//

#ifndef CALCEX_CALCULATOR_H
#define CALCEX_CALCULATOR_H

#include "Parser.h"

namespace detail
{
    class Calculator {
    public:
        Calculator(const TreeNode *root);
        void calculate() const;
    private:
        double calculateNode(const TreeNode * node) const;
    private:
        const TreeNode * _root;
    };


    inline Calculator::Calculator(const TreeNode *root) : _root{root} {}

}

#endif //CALCEX_CALCULATOR_H
