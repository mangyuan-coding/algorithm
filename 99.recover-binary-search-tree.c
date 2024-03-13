/*
 * @lc app=leetcode.cn id=99 lang=c
 *
 * [99] Recover Binary Search Tree
 */
#include "include/type.h"
#include <stdio.h>
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
#include <stdbool.h>

void find_problem_array(struct TreeNode *root, struct TreeNode **sorted, int *size)
{
    if (*size == 6)
    {
        return;
    }
    if (root->left != NULL)
    {
        find_problem_array(root->left, sorted, size);
    }
    if (*size == 6)
    {
        return;
    }
    (*size)++;
    sorted[*size - 1] = root;
    if (*size == 3)
    {
        if (sorted[0]->val <= sorted[1]->val && sorted[1]->val <= sorted[2]->val)
        {
            sorted[0] = sorted[2];
            sorted[1] = NULL;
            sorted[2] = NULL;
            *size = 1;
        }
    }
    else if (*size == 6)
    {
        if (sorted[2]->val <= sorted[3]->val && sorted[3]->val <= sorted[4]->val && sorted[4]->val <= sorted[5]->val)
        {
            sorted[3] = sorted[5];
            sorted[4] = NULL;
            sorted[5] = NULL;
            *size = 4;
        }
    }
    if (*size == 6)
    {
        return;
    }
    if (root->right != NULL)
    {
        find_problem_array(root->right, sorted, size);
    }
    if (*size == 6)
    {
        return;
    }
}

void recoverTree(struct TreeNode *root)
{
    int *size = (int *)malloc(sizeof(int));
    *size = 0;
    struct TreeNode **sorted = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * 6);
    find_problem_array(root, sorted, size);

    struct TreeNode *pro_1 = NULL, *pro_2 = NULL;
    if (*size == 2)
    {
        pro_1 = sorted[0];
        pro_2 = sorted[1];
    }
    else
    {
        for (int i = 0; i < *size; i++)
        {
            int smaller = 0;
            int bigger = 0;
            for (int j = 0; j < *size; j++)
            {
                if (i != j)
                {
                    if (sorted[i]->val > sorted[j]->val)
                    {
                        smaller++;
                    }
                }
            }
            if (smaller != i)
            {
                if (pro_1 == NULL)
                {
                    pro_1 = sorted[i];
                }
                else
                {
                    pro_2 = sorted[i];
                    break;
                }
            }
        }
    }

    int tmp = pro_1->val;
    pro_1->val = pro_2->val;
    pro_2->val = tmp;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    // [146,71,-13,55,null,231,399,321,null,null,null,null,null,-33]
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 68;
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 41;
    root->left->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left->val = -85;
    root->left->left->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left->left->val = -73;
    root->left->left->left->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left->left->left->val = -98;
    root->left->left->left->left->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left->left->left->left->val = -124;
    root->left->left->left->left->left->left = NULL;
    root->left->left->left->left->left->right = NULL;
    root->left->left->left->left->right = NULL;
    root->left->left->left->right = NULL;
    root->left->left->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left->right->val = -49;
    root->left->left->right->left = NULL;
    root->left->left->right->right = NULL;
    root->left->right = NULL;
    root->right = NULL;
    recoverTree(root);
    return 0;
}
