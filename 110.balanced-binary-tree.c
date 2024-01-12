/*
 * @lc app=leetcode id=110 lang=c
 *
 * [110] Balanced Binary Tree
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
#include <stdbool.h>
#include <math.h>

int measure_btree_height(struct TreeNode *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    int left_height = 0;
    if (root->left != NULL)
    {
        left_height = measure_btree_height(root->left);
        if (left_height == -1)
        {
            return -1;
        }
    }
    int right_height = 0;
    if (root->right != NULL)
    {
        right_height = measure_btree_height(root->right);
        if (right_height == -1)
        {
            return -1;
        }
    }

    if (abs(left_height - right_height) > 1)
    {
        return -1;
    }

    return fmax(left_height, right_height) + 1;
}

bool isBalanced(struct TreeNode *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
    {
        return true;
    }

    int left_height = 0;
    if (root->left != NULL)
    {
        left_height = measure_btree_height(root->left);
        if (left_height == -1)
        {
            return false;
        }
    }
    int right_height = 0;
    if (root->right != NULL)
    {
        right_height = measure_btree_height(root->right);
        if (right_height == -1)
        {
            return false;
        }
    }

    if (abs(left_height - right_height) > 1)
    {
        return false;
    }

    return true;
}
// @lc code=end
