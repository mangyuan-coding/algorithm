/*
 * @lc app=leetcode.cn id=162 lang=c
 *
 * [162] Find Peak Element
 */

// @lc code=start
int findPeakElement(int *nums, int numsSize)
{
    if (numsSize == 1)
    {
        return 0;
    }

    if (numsSize == 2)
    {
        return nums[0] > nums[1] ? 0 : 1;
    }

    int left = 0, right = numsSize - 1, half;
    while (left + 1 < right)
    {
        half = (left + right) / 2;
        if (nums[half - 1] < nums[half] && nums[half + 1] < nums[half])
        {
            return half;
        }

        if (nums[half - 1] > nums[half])
        {
            right = half;
        }
        else
        {
            left = half;
        }
    }
    return nums[left] > nums[right] ? left : right;
}
// @lc code=end
