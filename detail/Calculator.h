//
// Created by nikita on 7/6/19.
//

#ifndef CALCEX_CALCULATOR_H
#define CALCEX_CALCULATOR_H

#include "Parser.h"
#include <map>

namespace detail {
class Calculator
{
public:
    void calculate(const TreeNode *root);

private:
    double calculateNode(const TreeNode *node);

private:
    std::map<std::string, double> _variables;
};

} // namespace detail

#endif //CALCEX_CALCULATOR_H
