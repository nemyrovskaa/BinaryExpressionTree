#include "expression_tree.h"

ExpressionTree::ExpressionTree()
{
    operator_utils = OperatorUtils();
}

ExpressionTree::~ExpressionTree()
{
    // delete all trees in array
    for (int i = 0; i < (int)tree_root_arr.size(); i++)
    {
        recursiveDeleting(tree_root_arr[i]);
        delete tree_root_arr[i];
        tree_root_arr[i] = nullptr;
    }
}

void ExpressionTree::clearTree()
{
    // clear tree if not empty
    if (!tree_root_arr.empty())
    {
        for (int i = 0; i < (int)tree_root_arr.size(); i++)
        {
            recursiveDeleting(tree_root_arr[i]);
            tree_root_arr[i] = nullptr;
        }
        tree_root_arr.clear();
    }
}

void ExpressionTree::recursiveDeleting(TreeNode* this_node)
{
    if (this_node->left != nullptr)  // post-order traversal
    {
        recursiveDeleting(this_node->left);
        delete this_node->left;
        this_node->left = nullptr;

        if (this_node->right != nullptr)
        {
            recursiveDeleting(this_node->right);
            delete this_node->right;
            this_node->right = nullptr;
        }
    }
    return;
}

// parses expression string into array of operators and operands
std::vector<std::string> ExpressionTree::parseExpr(std::string& expression_str)
{
    int start_pos = 0;  // begin of word position
    int end_pos = 0;  // end of word position
    std::vector<std::string> res_arr;  // array of operators and operands
    std::string gap = " ";

    while (true)
    {
        start_pos = expression_str.find_first_not_of(gap, end_pos);  // first symbol, which is not gap
        if (start_pos == std::string::npos)  // break if there is no operators nor operands
            break;

        end_pos = expression_str.find_first_of(gap, start_pos);  // first gap after beginning of the word
        res_arr.push_back(expression_str.substr(start_pos, end_pos - start_pos));  // get this word
    }
    return res_arr;
}

// converts infix expression to postfix
std::vector<std::string> ExpressionTree::infixToPostfix(std::string& expression_str)
{
    std::vector<std::string> expression = parseExpr(expression_str); // parsed expression
    std::vector<std::string> stack;     // stack with operators
    std::vector<std::string> postfix;   // result, postfix expression
    std::string symb;  // symbol - operator or operand

    for (int i = 0; i < (int)expression.size(); i++)
    {
        symb = expression[i];

        // if symb is number, push it back in postfix expression
        if (!operator_utils.symbIsOperator(symb))
        {
            postfix.push_back(symb);
            continue;
        }

        // push back in stack if operator:
        // - is not ")"
        // - is "("
        // - is not "(" or ")" and stack is empty
        // - is not "(" or ")" and priority of this operator higher than last in stack
        if (symb != ")" && (symb == "(" || stack.empty() ||
            operator_utils.getPriority(symb) > operator_utils.getPriority(stack.back())))
        {
            stack.push_back(symb);
            continue;
        }

        // in other cases:
        // when ")" push back in postfix expression all operators until "("
        if (symb == ")")
        {
            while (!stack.empty() && stack.back() != "(")
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            if (!stack.empty() && stack.back() == "(")  // delete "(" in stack
                stack.pop_back();
        }
        else // while operator is associative and priority of this operator is less or equal to
        {    // the last in stack, push back operator in stack in postfix expression
            while (!stack.empty() && operator_utils.isAssociative(symb) &&
                operator_utils.getPriority(stack.back()) >= operator_utils.getPriority(symb))
            {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(symb);  // push back in stack this operator
        }
    }

    // if stack is not empty, push back all operators in stack to postfix expression
    while (!stack.empty())
    {
        postfix.push_back(stack.back());
        stack.pop_back();
    }

    return postfix;
}

// inserts node into the tree, used when building it
// data       - symbol to insert (operator or operand)
// is_num     - defines if data is a number (if it isn't, data is operator)
// is_postfix - defines that expression, being built, is postfix (otherwise it is prefix)
void ExpressionTree::insertNode(double data, bool is_num, bool is_postfix)
{
    // if data is a number, create new node
    // data in node is number => it is leaf
    if (is_num)
    {
        TreeNode* newTreeNode = new TreeNode(data, nullptr, nullptr);
        tree_root_arr.push_back(newTreeNode);
        return;
    }

    // if data is operator:
    // if there is less then two subtrees, error because operator must have two operands
    if (tree_root_arr.size() <= 1)
        throw std::length_error("Invalid input expression.");

    TreeNode* node_1 = tree_root_arr.back();  // get last subtree from array
    tree_root_arr.pop_back();
    TreeNode* node_2 = tree_root_arr.back();  // get second-to-last subtree from array
    tree_root_arr.pop_back();

    if (is_postfix)  // buid tree from postfix expression
        tree_root_arr.push_back(new TreeNode(data, node_2, node_1));  // left is second-to-last subtree from array, right is last subtree
    else  // build tree from prefix expression
        tree_root_arr.push_back(new TreeNode(data, node_1, node_2));  // left is last subtree from array, right is second-to-last subtree
    
    return;
}

// calculates the expression, traversing the tree (post-order traversal)
double ExpressionTree::calculate(TreeNode* this_node)
{
    double left = 0., right = 0.;  // left operand    right operand
    if ((this_node->left == nullptr) && (this_node->right == nullptr))
        return this_node->data;

    if (this_node->left != nullptr)
        left = calculate(this_node->left);

    if (this_node->right != nullptr)
        right = calculate(this_node->right);

    return operator_utils.getCalcFunc(operator_utils.getSymb(this_node->data))(left, right);
}

// builds the tree and calculates postfix expression
double ExpressionTree::calculatePostfixExpr(std::string& expression_str)
{
    std::vector<std::string> expression = parseExpr(expression_str);

    // iterate through expression string and build the tree
    for (auto symb : expression) // symb - symbol, operator or operand
    {
        if (operator_utils.getIdentifier(symb) != -1)  // symb is operator
            insertNode(operator_utils.getIdentifier(symb), false, true);
        else   // symb is operand
            insertNode(stod(symb), true, true);
    }

    // error if tree is not single (there are more subtrees)
    if (tree_root_arr.size() != 1 || tree_root_arr[0] == nullptr)
        throw std::length_error("Invalid input expression.");

    return calculate(tree_root_arr[0]);  // calculate expression in tree
}

// builds the tree and calculates infix expression
double ExpressionTree::calculateInfixExpr(std::string& expression_str)
{
    // parse and convert from infix to postfix
    std::vector<std::string> expression = infixToPostfix(expression_str);

    // iterate through expression string and build the tree
    for (auto symb : expression)
    {
        if (operator_utils.getIdentifier(symb) != -1)  // symb is operator
            insertNode(operator_utils.getIdentifier(symb), false, true);
        else   // symb is operand
            insertNode(std::stod(symb), true, true);
    }

    // error if tree is not single (there are more subtrees)
    if (tree_root_arr.size() != 1 || tree_root_arr[0] == nullptr)
        throw std::length_error("Invalid input expression.");

    return calculate(tree_root_arr[0]);  // calculate expression in tree
}

// builds the tree and calculates prefix expression
double ExpressionTree::calculatePrefixExpr(std::string& expression_str)
{
    std::vector<std::string> expression = parseExpr(expression_str);

    // iterate through expression string in inverse order and build the tree
    for (std::vector<std::string>::reverse_iterator it = expression.rbegin(); it != expression.rend(); ++it)
    {
        if (operator_utils.getIdentifier(*it) != -1)  // symb is operator
            insertNode(operator_utils.getIdentifier(*it), false, false);
        else   // symb is operand
            insertNode(std::stod(*it), true, false);
    }

    // error if tree is not single (there are more subtrees)
    if (tree_root_arr.size() != 1 || tree_root_arr[0] == nullptr)
        throw std::length_error("Invalid input expression.");

    return calculate(tree_root_arr[0]);  // calculate expression in tree
}