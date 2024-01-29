/*
 * @lc app=leetcode id=81 lang=c
 *
 * [81] Search in Rotated Sorted Array II
 */
#include <stdbool.h>
// @lc code=start

bool search(int *nums, int numsSize, int target)
{
    if (numsSize == 1)
    {
        return nums[0] == target;
    }
    if (nums[0] == target || nums[numsSize - 1] == target)
    {
        return true;
    }

    int left = 0, right = numsSize - 1, half;
    while (left < right)
    {
        half = (left + right) / 2;
        if (nums[half] == target)
        {
            return true;
        }
        if (half == left)
        {
            break;
        }

        if (nums[left] < nums[half])
        {
            if (target > nums[left] && target < nums[half])
            {
                right = half;
            }
            else
            {
                left = half;
            }
        }
        else if (nums[left] > nums[half])
        {
            if (target < nums[right] && target > nums[half])
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
            // nums[left] == nums[half] == nums[right]
            bool in_left = false;
            for (int i = left + 1; i < half; i++)
            {
                if (nums[i] != nums[half])
                {
                    if (nums[i] == target)
                    {
                        return true;
                    }
                    in_left = true;
                    break;
                }
            }
            if (in_left)
            {
                right = half;
            }
            else
            {
                left = half;
            }
        }
    }

    return false;
}
// @lc code=end
