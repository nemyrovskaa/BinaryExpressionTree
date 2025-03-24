#ifndef TREE_NODE_H_INCLUDED
#define TREE_NODE_H_INCLUDED


struct TreeNode
{
    double data;  // data in tree node
    TreeNode* left;  // pointer on the left node
    TreeNode* right;  // pointer on the right node

    // constructor of TreeNode
    TreeNode(double data, TreeNode* left, TreeNode* right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};


#endif // TREE_NODE_H_INCLUDED