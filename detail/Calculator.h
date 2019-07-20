//
// Created by nikita on 7/6/19.
//

#ifndef CALCEX_CALCULATOR_H
#define CALCEX_CALCULATOR_H

#include <map>
#include "parser/Tree.h"

namespace detail {
class Calculator
{
public:
    void calculate(const TreeNode *root);

private:
    double calculateNode(const TreeNode *node);

private:
    std::map<std::string, double *> _variablesMap;
};

} // namespace detail

#endif //CALCEX_CALCULATOR_H
