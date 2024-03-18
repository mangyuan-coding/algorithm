/*
 * @lc app=leetcode.cn id=113 lang=c
 *
 * [113] Path Sum II
 */
#include "include/utils.h"

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
#include <string.h>

const int MAX_SIZE = 5000;

int **paths = NULL;
int *each_path_size = NULL;
int path_size = 0;

void rebuild()
{
    if (paths != NULL)
    {
        free(paths);
    }
    if (each_path_size != NULL)
    {
        free(each_path_size);
    }
    path_size = 0;
    each_path_size = (int *)malloc(sizeof(int) * MAX_SIZE);
    paths = (int **)malloc(sizeof(int *) * MAX_SIZE);
}

void sub_tree_sum(struct TreeNode *node, int targetSum, int *pre, int pre_size)
{
    if (node->left != NULL || node->right != NULL)
    {
        int *cur = (int *)malloc(sizeof(int) * (pre_size + 1));
        memcpy(cur, pre, sizeof(int) * pre_size);
        cur[pre_size] = node->val;
        if (node->left != NULL)
        {
            sub_tree_sum(node->left, targetSum - node->val, cur, pre_size + 1);
        }
        if (node->right != NULL)
        {
            sub_tree_sum(node->right, targetSum - node->val, cur, pre_size + 1);
        }
        free(cur);
    }
    else
    {
        if (targetSum == node->val)
        {
            path_size++;
            each_path_size[path_size - 1] = pre_size + 1;
            paths[path_size - 1] = (int *)malloc(sizeof(int) * each_path_size[path_size - 1]);
            memcpy(paths[path_size - 1], pre, sizeof(int) * pre_size);
            paths[path_size - 1][pre_size] = node->val;
        }
    }
}

int **pathSum(struct TreeNode *root, int targetSum, int *returnSize, int **returnColumnSizes)
{
    rebuild();

    if (root == NULL)
    {
        *returnSize = 0;
        return NULL;
    }
    if (root->left == NULL && root->right == NULL)
    {
        if (targetSum == root->val)
        {
            *returnSize = 1;
            *returnColumnSizes = (int *)malloc(sizeof(int));
            (*returnColumnSizes)[0] = 1;
            int **ret = (int **)malloc(sizeof(int *));
            ret[0] = (int *)malloc(sizeof(int));
            ret[0][0] = root->val;
            return ret;
        }
        else
        {
            *returnSize = 0;
            return NULL;
        }
    }
    int *cur = (int *)malloc(sizeof(int));
    cur[0] = root->val;
    if (root->left != NULL)
    {
        sub_tree_sum(root->left, targetSum - root->val, cur, 1);
    }
    if (root->right != NULL)
    {
        sub_tree_sum(root->right, targetSum - root->val, cur, 1);
    }
    free(cur);
    *returnSize = path_size;
    *returnColumnSizes = (int *)malloc(sizeof(int) * path_size);
    for (int i = 0; i < path_size; i++)
    {
        (*returnColumnSizes)[i] = each_path_size[i];
    }
    return paths;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct TreeNode *root = build_tree("5,4,8,11,null,13,4,7,2,null,null,5,1", 13);
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **path = pathSum(root, 22, returnSize, returnColumnSizes);
    return 0;
}
