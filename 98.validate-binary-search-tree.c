/*
 * @lc app=leetcode.cn id=98 lang=c
 *
 * [98] Validate Binary Search Tree
 */

#include "include/type.h"
#include <stdbool.h>

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

int base;
int *pre_order;
int size;

void init()
{
    if (pre_order != NULL)
    {
        free(pre_order);
    }
    base = 100;
    pre_order = (int *)malloc(sizeof(int) * base);
    size = 0;
}

void build_pre_order(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        build_pre_order(root->left);
    }
    if (size == base - 1)
    {
        base *= 1.5;
        pre_order = (int *)realloc(pre_order, sizeof(int) * base);
    }
    pre_order[size++] = root->val;
    if (root->right != NULL)
    {
        build_pre_order(root->right);
    }
}

bool isValidBST(struct TreeNode *root)
{
    init();

    build_pre_order(root);

    for (int i = 1; i < size; i++)
    {
        if (pre_order[i] <= pre_order[i - 1])
        {
            return false;
        }
    }
    return true;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 2;
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 1;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->right->left = NULL;
    root->right->right = NULL;
    bool ret = isValidBST(root);
    return 0;
}
