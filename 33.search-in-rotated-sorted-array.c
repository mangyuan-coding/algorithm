/*
 * @lc app=leetcode id=33 lang=c
 *
 * [33] Search in Rotated Sorted Array
 */

// @lc code=start
int search(int *nums, int numsSize, int target)
{
    int left = 0, right = numsSize - 1, half;
    if (nums[0] == target)
    {
        return left;
    }
    if (nums[numsSize - 1] == target)
    {
        return numsSize - 1;
    }
    while (left < right)
    {
        half = (left + right) / 2;
        if (nums[half] == target)
        {
            return half;
        }
        if (half == left)
        {
            break;
        }
        if (nums[left] > nums[half])
        {
            if (nums[half] < target && nums[right] > target)
            {
                left = half;
            }
            else
            {
                right = half;
            }
        }
        else
        {
            if (nums[left] < target && nums[half] > target)
            {
                right = half;
            }
            else
            {
                left = half;
            }
        }
    }
    return -1;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {4, 5, 6, 7, 0, 1, 2};
    printf("index is %d", search(nums, 7, 3));
    return 0;
}
