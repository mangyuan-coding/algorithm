/*
 * @lc app=leetcode.cn id=153 lang=c
 *
 * [153] Find Minimum in Rotated Sorted Array
 */

// @lc code=start
int findMin(int *nums, int numsSize)
{
    if (numsSize == 1)
    {
        return nums[0];
    }

    int left = 0, right = numsSize - 1, half;
    while (left + 1 < right)
    {
        if (nums[left] < nums[right])
        {
            return nums[left];
        }

        half = (left + right) / 2;
        if (nums[half] > nums[right])
        {
            left = half;
        }
        else
        {
            right = half;
        }
    }

    return nums[left] > nums[right] ? nums[right] : nums[left];
}
// @lc code=end
