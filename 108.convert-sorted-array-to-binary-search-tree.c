/*
 * @lc app=leetcode id=108 lang=c
 *
 * [108] Convert Sorted Array to Binary Search Tree
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

struct TreeNode *bst = NULL;
int bst_idx = 0;

struct TreeNode *fill_tree(struct TreeNode *root, int *nums, int left, int right)
{
    if (left == right)
    {
        root->val = nums[left];
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    int half = (left + right) / 2;
    root->val = nums[half];

    if (half > left)
    {
        root->left = fill_tree(bst + (++bst_idx), nums, left, half - 1);
    }
    else
    {
        root->left = NULL;
    }

    if (half < right)
    {
        root->right = fill_tree(bst + (++bst_idx), nums, half + 1, right);
    }
    else
    {
        root->right = NULL;
    }

    return root;
}

struct TreeNode *sortedArrayToBST(int *nums, int numsSize)
{
    if (numsSize == 0)
    {
        return NULL;
    }
    if (numsSize == 1)
    {
        struct TreeNode *ret = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        ret[0].val = nums[0];
        ret->left = NULL;
        ret->right = NULL;
        return ret;
    }

    if (bst != NULL)
    {
        free(bst);
        bst_idx = 0;
    }
    bst = (struct TreeNode *)malloc(sizeof(struct TreeNode) * numsSize);

    int half = (numsSize - 1) / 2;
    bst->val = nums[half];

    if (half > 0)
    {
        bst->left = fill_tree(bst + (++bst_idx), nums, 0, half - 1);
    }
    else
    {
        bst->left = NULL;
    }
    if (half < numsSize - 1)
    {
        bst->right = fill_tree(bst + (++bst_idx), nums, half + 1, numsSize - 1);
    }
    else
    {
        bst->right = NULL;
    }
    return bst;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[2] = {1, 3};

    struct TreeNode *bst = sortedArrayToBST(nums, 2);

    return 0;
}
