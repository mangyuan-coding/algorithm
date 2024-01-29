/*
 * @lc app=leetcode id=144 lang=c
 *
 * [144] Binary Tree Preorder Traversal
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int *preorderTraversal(struct TreeNode *root, int *returnSize)
{
    if (root == NULL)
    {
        *returnSize = 0;
        return NULL;
    }
    if (root->left == NULL && root->right == NULL)
    {
        *returnSize = 1;
        int *traversal = (int *)malloc(sizeof(int));
        traversal[0] = root->val;
        return traversal;
    }
    *returnSize = 0;
    int *traversal = (int *)malloc(sizeof(int) * 100);
    struct TreeNode **trace = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * 100);

    int trace_idx = 0;
    trace[trace_idx] = root;
    while (trace_idx >= 0)
    {
        struct TreeNode *cur = trace[trace_idx--];
        traversal[(*returnSize)++] = cur->val;
        if (cur->right != NULL)
        {
            trace[++trace_idx] = cur->right;
        }
        if (cur->left != NULL)
        {
            trace[++trace_idx] = cur->left;
        }
    }
    return traversal;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = NULL;
    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 2;
    root->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right = NULL;
    root->right->left->val = 3;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    int *returnSize = (int *)malloc(sizeof(int));
    preorderTraversal(root, returnSize);
    return 0;
}
