#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED


#include <vector>
#include <string>
#include "tree_node.h"
#include "operator_utils.h"

class ExpressionTree
{
private:
    std::vector <TreeNode*>tree_root_arr;
    OperatorUtils operator_utils;

    void clearTree();
    void recursiveDeleting(TreeNode* this_node);
    std::vector<std::string> parseExpr(std::string& expression_str);
    std::vector<std::string> infixToPostfix(std::string& expression_str);
    void insertNode(double data, bool is_num, bool is_postfix);
    double calculate(TreeNode* this_node);

public:
    ExpressionTree();
    ~ExpressionTree();
    double calculatePostfixExpr(std::string& expression_str);
    double calculateInfixExpr(std::string& expression_str);
    double calculatePrefixExpr(std::string& expression_str);
};


#endif // TREE_H_INCLUDED