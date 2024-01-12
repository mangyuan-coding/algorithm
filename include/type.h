#include <stdlib.h>

/**
 * Single linked Node
 */
struct ListNode
{
    int val;
    struct ListNode *next;
};

/**
 *
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};