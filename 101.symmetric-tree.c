/*
 * @lc app=leetcode id=101 lang=c
 *
 * [101] Symmetric Tree
 */
#include <stdbool.h>
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
#include <stdlib.h>

bool is_symmetric(struct TreeNode *left, struct TreeNode *right)
{
    if (left == NULL && right == NULL)
    {
        return true;
    }
    if (left == NULL || right == NULL)
    {
        return false;
    }

    return left->val == right->val && is_symmetric(left->left, right->right) && is_symmetric(left->right, right->left);
}

bool isSymmetric(struct TreeNode *root)
{
    return is_symmetric(root->left, root->right);
}
// @lc code=end
