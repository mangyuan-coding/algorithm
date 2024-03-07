/*
 * @lc app=leetcode id=95 lang=c
 *
 * [95] Unique Binary Search Trees II
 */
#include <stdio.h>
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

struct TreeNode *tree_deep_clone(struct TreeNode *source)
{
    struct TreeNode *target = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    target->val = source->val;
    if (source->left == NULL)
    {
        target->left = NULL;
    }
    else
    {
        target->left = tree_deep_clone(source->left);
    }
    if (source->right == NULL)
    {
        target->right = NULL;
    }
    else
    {
        target->right = tree_deep_clone(source->right);
    }
    return target;
}

struct TreeNode **generateTrees(int n, int *returnSize)
{
    int **sub_tree_size = (int **)malloc(sizeof(int *) * n);
    struct TreeNode ****sub_trees = (struct TreeNode ****)malloc(sizeof(struct TreeNode ***) * n);
    for (int i = 0; i < n; i++)
    {
        sub_tree_size[i] = (int *)malloc(sizeof(int) * n);
        sub_trees[i] = (struct TreeNode ***)malloc(sizeof(struct TreeNode **) * n);
    }

    for (int distence = 0, ideal_size; distence < n; distence++)
    {
        for (int i = 0, j; i < n - distence; i++)
        {
            if (distence == 0)
            {
                ideal_size = 1;
                sub_trees[i][i] = (struct TreeNode **)malloc(sizeof(struct TreeNode *));
                sub_tree_size[i][i] = ideal_size;
                sub_trees[i][i][sub_tree_size[i][i] - 1] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                sub_trees[i][i][sub_tree_size[i][i] - 1]->val = i + 1;
                sub_trees[i][i][sub_tree_size[i][i] - 1]->left = NULL;
                sub_trees[i][i][sub_tree_size[i][i] - 1]->right = NULL;
            }
            else
            {
                j = i + distence;
                ideal_size = 0;
                for (int root = i; root <= j; root++)
                {
                    if (i > root - 1)
                    {
                        ideal_size += sub_tree_size[root + 1][j];
                    }
                    else if (root + 1 > j)
                    {
                        ideal_size += sub_tree_size[i][root - 1];
                    }
                    else
                    {
                        ideal_size += sub_tree_size[i][root - 1] * sub_tree_size[root + 1][j];
                    }
                }
                sub_trees[i][j] = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * ideal_size);
                sub_tree_size[i][j] = 0;
                for (int root = i; root <= j; root++)
                {
                    if (i > root - 1)
                    {
                        for (int idx_of_sub = 0; idx_of_sub < sub_tree_size[root + 1][j]; idx_of_sub++)
                        {
                            sub_tree_size[i][j]++;
                            sub_trees[i][j][sub_tree_size[i][j] - 1] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                            sub_trees[i][j][sub_tree_size[i][j] - 1]->val = root + 1;
                            sub_trees[i][j][sub_tree_size[i][j] - 1]->left = NULL;
                            sub_trees[i][j][sub_tree_size[i][j] - 1]->right = tree_deep_clone(sub_trees[root + 1][j][idx_of_sub]);
                        }
                    }
                    else if (root + 1 > j)
                    {
                        // sub_tree_size[i][root - 1];
                        for (int idx_of_sub = 0; idx_of_sub < sub_tree_size[i][root - 1]; idx_of_sub++)
                        {
                            sub_tree_size[i][j]++;
                            sub_trees[i][j][sub_tree_size[i][j] - 1] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                            sub_trees[i][j][sub_tree_size[i][j] - 1]->val = root + 1;
                            sub_trees[i][j][sub_tree_size[i][j] - 1]->left = tree_deep_clone(sub_trees[i][root - 1][idx_of_sub]);
                            sub_trees[i][j][sub_tree_size[i][j] - 1]->right = NULL;
                        }
                    }
                    else
                    {
                        // sub_tree_size[i][root - 1] * sub_tree_size[root + 1][j];

                        for (int idx_of_left = 0; idx_of_left < sub_tree_size[i][root - 1]; idx_of_left++)
                        {
                            for (int idx_of_right = 0; idx_of_right < sub_tree_size[root + 1][j]; idx_of_right++)
                            {
                                sub_tree_size[i][j]++;
                                sub_trees[i][j][sub_tree_size[i][j] - 1] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                                sub_trees[i][j][sub_tree_size[i][j] - 1]->val = root + 1;
                                sub_trees[i][j][sub_tree_size[i][j] - 1]->left = tree_deep_clone(sub_trees[i][root - 1][idx_of_left]);
                                sub_trees[i][j][sub_tree_size[i][j] - 1]->right = tree_deep_clone(sub_trees[root + 1][j][idx_of_right]);
                            }
                        }
                    }
                }
            }
        }
    }
    *returnSize = sub_tree_size[0][n - 1];
    return sub_trees[0][n - 1];
}
// @lc code=end

void print_tree(struct TreeNode *tree)
{
    printf("%d ", tree->val);
    if (tree->left != NULL)
    {
        print_tree(tree->left);
    }
    else
    {
        printf("NULL ");
    }
    if (tree->right != NULL)
    {
        print_tree(tree->right);
    }
    else
    {
        printf("NULL ");
    }
}

int main(int argc, char const *argv[])
{
    int *returnSize = (int *)malloc(sizeof(int));
    struct TreeNode **trees = generateTrees(3, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("[ ");
        print_tree(trees[i]);
        printf("] \n");
    }

    return 0;
}
