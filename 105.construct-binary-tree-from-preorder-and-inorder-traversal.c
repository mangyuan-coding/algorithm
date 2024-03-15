/*
 * @lc app=leetcode.cn id=105 lang=c
 *
 * [105] Construct Binary Tree from Preorder and Inorder Traversal
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

struct TreeNode *build_sub_tree(int *preorder, int pre_start, int pre_end, int *inorder, int in_start, int in_end)
{
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = preorder[pre_start];

    int idx_of_in_order = in_start;
    for (; idx_of_in_order < in_end; idx_of_in_order++)
    {
        if (inorder[idx_of_in_order] == preorder[pre_start])
        {
            break;
        }
    }

    if (idx_of_in_order != in_start)
    {

        node->left = build_sub_tree(preorder, pre_start + 1, idx_of_in_order - in_start + pre_start, inorder, in_start, idx_of_in_order - 1);
    }
    else
    {
        node->left = NULL;
    }
    if (idx_of_in_order != in_end)
    {
        node->right = build_sub_tree(preorder, idx_of_in_order - in_start + pre_start + 1, pre_end, inorder, idx_of_in_order + 1, in_end);
    }
    else
    {
        node->right = NULL;
    }
    return node;
}

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];

    int idx_of_in_order = 0;
    for (; idx_of_in_order < inorderSize; idx_of_in_order++)
    {
        if (inorder[idx_of_in_order] == preorder[0])
        {
            break;
        }
    }

    if (idx_of_in_order != 0)
    {
        root->left = build_sub_tree(preorder, 1, idx_of_in_order, inorder, 0, idx_of_in_order - 1);
    }
    else
    {
        root->left = NULL;
    }
    if (idx_of_in_order != inorderSize - 1)
    {
        root->right = build_sub_tree(preorder, idx_of_in_order + 1, preorderSize - 1, inorder, idx_of_in_order + 1, inorderSize - 1);
    }
    else
    {
        root->right = NULL;
    }
    return root;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int size = 3;
    int *preorder = (int *)malloc(sizeof(int) * size);
    preorder[0] = 1;
    preorder[1] = 2;
    preorder[2] = 3;
    int *inorder = (int *)malloc(sizeof(int) * size);
    inorder[0] = 3;
    inorder[1] = 2;
    inorder[2] = 1;
    struct TreeNode *root = buildTree(preorder, size, inorder, size);
    return 0;
}
