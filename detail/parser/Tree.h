#ifndef CALCEX_TREE_H
#define CALCEX_TREE_H

namespace detail {

struct TreeItem
{
    TokenType token;
	std::any
	union
    {
        double value;
        double *variable;
        Operator _operator;
    };

    TreeItem(double val);
    TreeItem(double *var);
    TreeItem(Operator op);
};

inline TreeItem::TreeItem(double val) : value{val}, token{TokenType::Number} {}
inline TreeItem::TreeItem(double *var) : variable{var}, token{TokenType::Variable} {}
inline TreeItem::TreeItem(Operator op) : _operator{op}, token{TokenType::Operator} {}

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;

    TreeItem value;

    TreeNode(TreeItem &&v);
    ~TreeNode();
};

inline TreeNode::TreeNode(TreeItem &&v)
    : value{v}, left{}, right{}
{}

inline TreeNode::~TreeNode()
{
    if (left) delete left;
    if (right) delete right;
}

} // namespace detail

#endif //CALCEX_TREE_H