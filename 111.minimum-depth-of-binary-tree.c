/*
 * @lc app=leetcode id=111 lang=c
 *
 * [111] Minimum Depth of Binary Tree
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
#include <math.h>
#include <stdbool.h>

int min_depth(struct TreeNode *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    if (root->left == NULL)
    {
        return min_depth(root->right) + 1;
    }
    else if (root->right == NULL)
    {
        return min_depth(root->left) + 1;
    }
    else
    {
        return fmin(min_depth(root->left), min_depth(root->right)) + 1;
    }
}

int minDepth(struct TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    if (root->left == NULL)
    {
        return minDepth(root->right) + 1;
    }
    if (root->right == NULL)
    {
        return minDepth(root->left) + 1;
    }

    return fmin(min_depth(root->left), min_depth(root->right)) + 1;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 3;

    root->left->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left->val = 4;
    root->left->right = NULL;
    root->left->left->left = NULL;
    root->left->left->right = NULL;

    root->right->left = NULL;
    root->right->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right->val = 5;
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    printf("%d", minDepth(root));
    return 0;
}
