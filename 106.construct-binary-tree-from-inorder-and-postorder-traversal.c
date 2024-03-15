/*
 * @lc app=leetcode.cn id=106 lang=c
 *
 * [106] Construct Binary Tree from Inorder and Postorder Traversal
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
#include <stdlib.h>

struct TreeNode *build_sub_tree(int *inorder, int in_start, int in_end, int *postorder, int post_start, int post_end)
{
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = postorder[post_end];

    int idx_of_in = in_start;
    while (idx_of_in <= in_end && node->val != inorder[idx_of_in])
    {
        idx_of_in++;
    }

    if (idx_of_in != in_start)
    {
        node->left = build_sub_tree(inorder, in_start, idx_of_in - 1, postorder, post_start, idx_of_in - in_start + post_start - 1);
    }
    else
    {
        node->left = NULL;
    }

    if (idx_of_in != in_end)
    {
        node->right = build_sub_tree(inorder, idx_of_in + 1, in_end, postorder, idx_of_in - in_start + post_start, post_end - 1);
    }
    else
    {
        node->right = NULL;
    }

    return node;
}

struct TreeNode *buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize)
{
    return build_sub_tree(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}
// @lc code=end
