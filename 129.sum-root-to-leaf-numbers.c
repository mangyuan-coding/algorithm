/*
 * @lc app=leetcode.cn id=129 lang=c
 *
 * [129] Sum Root to Leaf Numbers
 */

#include "include/type.h"

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int sum = 0;

void sum_sub_tree(int pre, struct TreeNode *root)
{
    int cur = pre * 10 + root->val;
    if (root->left == NULL && root->right == NULL)
    {
        sum += cur;
    }
    else if (root->left != NULL || root->right != NULL)
    {
        if (root->left != NULL)
        {
            sum_sub_tree(cur, root->left);
        }
        if (root->right != NULL)
        {
            sum_sub_tree(cur, root->right);
        }
    }
}

int sumNumbers(struct TreeNode *root)
{
    sum = 0;
    sum_sub_tree(0, root);
    return sum;
}
// @lc code=end
