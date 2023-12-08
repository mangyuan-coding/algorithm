/*
 * @lc app=leetcode id=27 lang=c
 *
 * [27] Remove Element
 */

// @lc code=start
int removeElement(int *nums, int numsSize, int val)
{
    if (numsSize == 0)
    {
        return 0;
    }
    int left = 0, right = numsSize - 1;
    while (left <= right)
    {
        if (nums[left] == val)
        {
            nums[left] = nums[right--];
        }
        else
        {
            left++;
        }
    }
    return left;
}
// @lc code=end