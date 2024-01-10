/*
 * @lc app=leetcode id=94 lang=c
 *
 * [94] Binary Tree Inorder Traversal
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

void read_tree(struct TreeNode *root, int *ret, int *return_size, int *base)
{
    if (root == NULL)
    {
        return;
    }
    read_tree(root->left, ret, return_size, base);

    if (*return_size == *base)
    {
        (*base) *= 1.5;
        ret = (int *)realloc(ret, sizeof(int) * *base);
    }
    (*return_size)++;
    ret[*return_size - 1] = root->val;
    read_tree(root->right, ret, return_size, base);
}

int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    if (root == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    int *base = (int *)malloc(sizeof(int));
    *base = 100;
    int *ret = (int *)malloc(sizeof(int) * *base);
    int *return_size = (int *)malloc(sizeof(int));
    *return_size = 0;

    read_tree(root, ret, return_size, base);
    *returnSize = *return_size;

    return ret;
}
// @lc code=end
#include <stdio.h>

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
    int *ret = inorderTraversal(root, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%d ", ret[i]);
    }

    return 0;
}
