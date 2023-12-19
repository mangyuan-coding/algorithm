/*
 * @lc app=leetcode id=34 lang=c
 *
 * [34] Find First and Last Position of Element in Sorted Array
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    int *ret = malloc(sizeof(int) * 2);
    ret[0] = -1;
    ret[1] = -1;
    *returnSize = 2;

    if (numsSize < 1 || nums[0] > target || nums[numsSize - 1] < target)
    {
        return ret;
    }

    if (numsSize == 1)
    {
        if (nums[0] == target)
        {
            ret[0] = 0;
            ret[1] = 0;
        }
        return ret;
    }

    int target_left, target_right;

    double smaller = target - 0.5;
    int left = 0, right = numsSize - 1, half;
    if (smaller < nums[0])
    {
        target_left = left;
    }
    else
    {
        while (left < right)
        {
            half = (left + right) / 2;
            if (half == left && right - left <= 1)
            {
                break;
            }
            if (nums[half] < smaller)
            {
                left = half;
            }
            else
            {
                right = half;
            }
        }
        target_left = right;
    }

    left = 0, right = numsSize - 1;
    double bigger = target + 0.5;
    if (bigger > nums[right])
    {
        target_right = right;
    }
    else
    {
        while (left < right)
        {
            half = (left + right) / 2;
            if (half == left)
            {
                break;
            }
            if (nums[half] < bigger)
            {
                left = half;
            }
            else
            {
                right = half;
            }
        }
        target_right = left;
    }

    if (target_left > target_right)
    {
        return ret;
    }

    ret[0] = target_left;
    ret[1] = target_right;
    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {1, 3};
    int *returnSize = malloc(sizeof(int));
    int *ret = searchRange(nums, 2, 1, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("nums %d is %d \n", i, ret[i]);
    }
    return 0;
}
