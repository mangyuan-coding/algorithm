/*
 * @lc app=leetcode id=35 lang=c
 *
 * [35] Search Insert Position
 */

// @lc code=start
int searchInsert(int *nums, int numsSize, int target)
{
    if (numsSize <= 0)
    {
        return 0;
    }
    if (numsSize == 1)
    {
        if (nums[0] >= target)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (nums[0] >= target)
    {
        return 0;
    }
    if (nums[numsSize - 1] < target)
    {
        return numsSize;
    }

    int left = 0, right = numsSize - 1, half;
    while (left < right)
    {
        half = (left + right) / 2;
        if (left == half)
        {
            break;
        }
        if (nums[half] == target)
        {
            return half;
        }
        else if (nums[half] > target)
        {
            right = half;
        }
        else
        {
            left = half;
        }
    }
    return right;
}
// @lc code=end
