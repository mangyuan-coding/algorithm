/*
 * @lc app=leetcode.cn id=107 lang=c
 *
 * [107] Binary Tree Level Order Traversal II
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
const int MAX_SIZE = 2000;

int **levelOrderBottom(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    if (root == NULL)
    {
        *returnSize = 0;
        return NULL;
    }
    // define
    struct TreeNode **node_queue = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * MAX_SIZE);
    int node_size = 0;
    *returnColumnSizes = (int *)malloc(sizeof(int) * (MAX_SIZE + 1));
    *returnSize = 0;

    (*returnColumnSizes)[(*returnSize)++] = 1;
    node_queue[node_size++] = root;

    while (1)
    {
        int pre_deep = *returnSize - 1;
        int pre_end = node_size - 1;

        (*returnColumnSizes)[(*returnSize)++] = 0;
        for (int pre_start = node_size - (*returnColumnSizes)[pre_deep]; pre_start <= pre_end; pre_start++)
        {
            if (node_queue[pre_start]->left != NULL)
            {
                (*returnColumnSizes)[*returnSize - 1]++;
                node_queue[node_size++] = node_queue[pre_start]->left;
            }
            if (node_queue[pre_start]->right != NULL)
            {
                (*returnColumnSizes)[*returnSize - 1]++;
                node_queue[node_size++] = node_queue[pre_start]->right;
            }
        }
        if (pre_end == node_size - 1)
        {
            (*returnSize)--;
            break;
        }
    }

    int **order = (int **)malloc(sizeof(int *) * (*returnSize));
    for (int deep = *returnSize - 1; deep >= 0; deep--)
    {
        order[*returnSize - deep - 1] = (int *)malloc(sizeof(int) * (*returnColumnSizes)[deep]);
        for (int i = 0; i < (*returnColumnSizes)[deep]; i++)
        {
            order[*returnSize - deep - 1][i] = node_queue[node_size - (*returnColumnSizes)[deep] + i]->val;
        }
        node_size -= (*returnColumnSizes)[deep];
    }

    for (int i = 0; i < *returnSize / 2; i++)
    {
        int tmp = (*returnColumnSizes)[i];
        (*returnColumnSizes)[i] = (*returnColumnSizes)[*returnSize - i - 1];
        (*returnColumnSizes)[*returnSize - i - 1] = tmp;
    }

    free(node_queue);

    return order;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->right->left = NULL;
    root->right->right = NULL;

    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **order = levelOrderBottom(root, returnSize, returnColumnSizes);

    printf("[");
    for (int i = 0; i < *returnSize; i++)
    {
        printf("returnColumnSizes is %d", (*returnColumnSizes)[i]);
        printf("[");
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d,", order[i][j]);
        }
        printf("],");
    }
    printf("]");

    return 0;
}
