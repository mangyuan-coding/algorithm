/*
 * @lc app=leetcode.cn id=103 lang=c
 *
 * [103] Binary Tree Zigzag Level Order Traversal
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
#include <stdlib.h>
#include <stdbool.h>

const int MAXIMUM = 2001;

int **zigzagLevelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    if (root == NULL)
    {
        return NULL;
    }

    int **order = (int **)malloc(sizeof(int *) * MAXIMUM);
    *returnColumnSizes = (int *)malloc(sizeof(int) * MAXIMUM);

    struct TreeNode **pre_queue = (struct TreeNode **)malloc(sizeof(struct TreeNode *)), **cur_queue;

    int pre_size = 1, cur_size = 0;
    pre_queue[pre_size - 1] = root;

    *returnSize = 1;
    (*returnColumnSizes)[0] = 1;
    order[0] = (int *)malloc(sizeof(int));
    order[0][0] = root->val;

    int deep = 2;
    bool inverse = true;
    while (1)
    {
        if (pre_size == 0)
        {
            break;
        }
        (*returnSize)++;
        order[*returnSize - 1] = (int *)malloc(sizeof(int) * pre_size * 2);
        cur_size = 0;
        cur_queue = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * pre_size * 2);
        // first put cur
        for (int i = 0; i < pre_size; i++)
        {
            struct TreeNode *node = pre_queue[i];
            if (node->left != NULL)
            {
                cur_queue[cur_size++] = node->left;
                order[*returnSize - 1][cur_size - 1] = node->left->val;
            }
            if (node->right != NULL)
            {
                cur_queue[cur_size++] = node->right;
                order[*returnSize - 1][cur_size - 1] = node->right->val;
            }
        }
        if (inverse)
        {
            if (cur_size > 1)
            {
                for (int i = 0; i < cur_size / 2; i++)
                {
                    int tmp = order[*returnSize - 1][i];
                    order[*returnSize - 1][i] = order[*returnSize - 1][cur_size - i - 1];
                    order[*returnSize - 1][cur_size - i - 1] = tmp;
                }
            }
        }
        inverse = !inverse;
        (*returnColumnSizes)[*returnSize - 1] = cur_size;
        free(pre_queue);
        pre_size = cur_size;
        pre_queue = cur_queue;
    }
    (*returnSize)--;
    return order;
}
// @lc code=end
