/*
 * @lc app=leetcode.cn id=114 lang=c
 *
 * [114] Flatten Binary Tree to Linked List
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

struct TreeNode *flatten_left_tree_and_return_tail(struct TreeNode *node)
{
    if (node == NULL || (node->left == NULL && node->right == NULL))
    {
        return node;
    }

    struct TreeNode *right = node->right, *tail;
    if (node->left != NULL)
    {
        struct TreeNode *left_tail = flatten_left_tree_and_return_tail(node->left);
        node->right = node->left;
        if (right == NULL)
        {
            tail = left_tail;
        }
        else
        {
            left_tail->right = right;
        }

        node->left = NULL;
    }
    if (right != NULL)
    {
        return flatten_left_tree_and_return_tail(right);
    }
    return tail;
}

void flatten(struct TreeNode *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
    {
        return;
    }
    struct TreeNode *right = root->right;
    if (root->left != NULL)
    {
        struct TreeNode *tail = flatten_left_tree_and_return_tail(root->left);
        root->right = root->left;
        tail->right = right;
        root->left = NULL;
    }
    if (right != NULL)
    {
        flatten(root->right);
    }
}
// @lc code=end
