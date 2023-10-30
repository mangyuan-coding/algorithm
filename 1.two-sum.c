/*
 * @lc app=leetcode id=1 lang=c
 *
 * [1] Two Sum
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include "uthash/src/uthash.h"

struct node
{
    int num;
    int index;
    UT_hash_handle hh;
};

struct node *nodes = NULL;

void addNode(int num, int index)
{
    struct node *node;
    HASH_FIND_INT(nodes, num, node);
    if (node == NULL)
    {
        node = (struct node *)malloc(sizeof *node);
        node->num = num;
        node->index = index;
    }
};

struct node *findNode(int num)
{
    struct node *node;
    HASH_FIND_INT(nodes, num, node);
    return node;
};

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int ret[2];

    struct node *first_node;
    first_node = (struct indexed_num *)malloc(sizeof *first_node);
    first_node->num = nums[0];
    first_node->index = 0;

    HASH_ADD_INT(nodes, num, first_node);

    for (int i = 1; i < numsSize; i++)
    {
        int remain = target - nums[i];
        struct node *remain_node = findNode(nodes, remain);
        if (remain_node != NULL)
        {
            ret[0] = remain_node->index;
            ret[1] = i;
            return *ret;
        }
        else
        {
            addNode(nodes, nums[i], i);
        }
    }

    return ret;
}
// @lc code=end

