/*
 * @lc app=leetcode id=1 lang=c
 *
 * [1] Two Sum
 */
#include "uthash/src/uthash.h"

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct node
{
    int key;
    int val;
    UT_hash_handle hh;
};

struct node *nodes;

struct node *find(int ikey)
{
    struct node *tmp;
    HASH_FIND_INT(nodes, &ikey, tmp);
    return tmp;
}

void insert(int ikey, int ival)
{
    struct node *it = find(ikey);
    if (it == NULL)
    {
        struct node *tmp = malloc(sizeof(struct node));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(nodes, key, tmp);
    }
    else
    {
        it->val = ival;
    }
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    nodes = NULL;
    for (int i = 0; i < numsSize; i++)
    {
        struct node *it = find(target - nums[i]);
        if (it != NULL)
        {
            int *ret = malloc(sizeof(int) * 2);
            ret[0] = it->val, ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        insert(nums[i], i);
    }
    *returnSize = 0;
    return NULL;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    // test-case 1
    // int numsSize = 4;
    // int *nums = malloc(sizeof(int) * numsSize);
    // nums[0] = 2;
    // nums[1] = 7;
    // nums[2] = 11;
    // nums[3] = 15;
    // int target = 9;

    // test-case 2
    // int numsSize = 3;
    // int *nums = malloc(sizeof(int) * numsSize);
    // nums[0] = 3;
    // nums[1] = 2;
    // nums[2] = 4;
    // int target = 6;

    // test-case 3
    // int numsSize = 4;
    // int *nums = malloc(sizeof(int) * numsSize);
    // nums[0] = -10;
    // nums[1] = 7;
    // nums[2] = 19;
    // nums[3] = 15;
    // int target = 9;

    // test-case 4
    int numsSize = 2;
    int *nums = malloc(sizeof(int) * numsSize);
    nums[0] = 3;
    nums[1] = 3;
    int target = 6;

    int *returnSize = malloc(sizeof(int));
    int *ret = twoSum(nums, numsSize, target, returnSize);
    if (ret != NULL)
    {
        printf("第一个位置：%d，第二个位置：%d", ret[0], ret[1]);
    }

    return 0;
}
