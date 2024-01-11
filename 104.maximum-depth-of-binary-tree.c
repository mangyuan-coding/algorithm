/*
 * @lc app=leetcode id=104 lang=c
 *
 * [104] Maximum Depth of Binary Tree
 */
#include "include/type.h"
#include <stdlib.h>

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <math.h>

int max_depth(struct TreeNode *left, struct TreeNode *right);

int maxDepth(struct TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return max_depth(root->left, root->right) + 1;
}

int max_depth(struct TreeNode *left, struct TreeNode *right)
{
    if (left == NULL && right == NULL)
    {
        return 0;
    }
    if (left == NULL)
    {
        return maxDepth(right);
    }
    if (right == NULL)
    {
        return maxDepth(left);
    }

    return fmax(maxDepth(left), maxDepth(right));
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 3;
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 9;
    root->left->left = NULL;
    root->left->right = NULL;

    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 20;
    root->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->left->val = 15;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right->val = 7;
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    printf("%d", maxDepth(root));
    return 0;
}
