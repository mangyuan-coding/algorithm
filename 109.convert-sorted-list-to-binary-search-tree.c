/*
 * @lc app=leetcode.cn id=109 lang=c
 *
 * [109] Convert Sorted List to Binary Search Tree
 */
#include "include/type.h"
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>

const int MAX_NODE_SIZE = 20000;

struct TreeNode *build_sub_BST_ret_root(struct TreeNode **sorted_node, int start, int end)
{
    int hlaf = (start + end) / 2;
    struct TreeNode *root = sorted_node[hlaf];

    if (hlaf > start)
    {
        root->left = build_sub_BST_ret_root(sorted_node, start, hlaf - 1);
    }
    if (hlaf < end)
    {
        root->right = build_sub_BST_ret_root(sorted_node, hlaf + 1, end);
    }

    return root;
}

struct TreeNode *sortedListToBST(struct ListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    struct TreeNode **sorted_node = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * MAX_NODE_SIZE);
    int size = 0;

    while (head != NULL)
    {
        size++;
        sorted_node[size - 1] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        sorted_node[size - 1]->val = head->val;
        sorted_node[size - 1]->left = NULL;
        sorted_node[size - 1]->right = NULL;
        head = head->next;
    }

    int hlaf = size / 2;
    struct TreeNode *BST = sorted_node[hlaf];

    if (hlaf > 0)
    {
        BST->left = build_sub_BST_ret_root(sorted_node, 0, hlaf - 1);
    }
    if (hlaf < size - 1)
    {
        BST->right = build_sub_BST_ret_root(sorted_node, hlaf + 1, size - 1);
    }

    free(sorted_node);

    return BST;
}
// @lc code=end
