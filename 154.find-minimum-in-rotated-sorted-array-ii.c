/*
 * @lc app=leetcode.cn id=154 lang=c
 *
 * [154] Find Minimum in Rotated Sorted Array II
 *
 * https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/description/
 *
 * algorithms
 * Hard (51.92%)
 * Likes:    694
 * Dislikes: 0
 * Total Accepted:    199.5K
 * Total Submissions: 384.2K
 * Testcase Example:  '[1,3,5]'
 *
 * Suppose an array of length n sorted in ascending order is rotated between 1
 * and n times. For example, the array nums = [0,1,4,4,5,6,7] might
 * become:
 *
 *
 * [4,5,6,7,0,1,4] if it was rotated 4 times.
 * [0,1,4,4,5,6,7] if it was rotated 7 times.
 *
 *
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
 * in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums that may contain duplicates, return the
 * minimum element of this array.
 *
 * You must decrease the overall operation steps as much as possible.
 *
 *
 * Example 1:
 * Input: nums = [1,3,5]
 * Output: 1
 * Example 2:
 * Input: nums = [2,2,2,0,1]
 * Output: 0
 *
 *
 * Constraints:
 *
 *
 * n == nums.length
 * 1 <= n <= 5000
 * -5000 <= nums[i] <= 5000
 * nums is sorted and rotated between 1 and n times.
 *
 *
 *
 * Follow up: This problem is similar to Find Minimum in Rotated Sorted Array,
 * but nums may contain duplicates. Would this affect the runtime complexity?
 * How and why?
 *
 *
 *
 */

#include <math.h>
#include <stdlib.h>

// @lc code=start

void find_diff_range(int *nums, int start, int end, int *diff_start, int *diff_end)
{
    if (start + 1 == end)
    {
        return;
    }
    int half = (start + end) / 2;
    if (nums[half] != nums[start])
    {
        (*diff_start) = start;
        (*diff_end) = end;
    }
    else
    {
        find_diff_range(nums, start, half, diff_start, diff_end);
        if ((*diff_start) != -1)
        {
            return;
        }
        find_diff_range(nums, half, end, diff_start, diff_end);
    }
}

int findMin(int *nums, int numsSize)
{
    if (numsSize == 1)
    {
        return nums[0];
    }
    if (numsSize == 2)
    {
        return fmin(nums[0], nums[1]);
    }
    if (nums[numsSize - 1] > nums[0])
    {
        return nums[0];
    }
    int *diff_start = calloc(1, sizeof(int)), *diff_end = calloc(1, sizeof(int));
    int left = 0, right = numsSize - 1, half = (left + right) / 2;
    while (left + 1 < right)
    {
        if (nums[left] > nums[half])
        {
            right = half;
            half = (left + right) / 2;
        }
        else if (nums[left] < nums[half] || nums[half] != nums[right])
        {
            left = half;
            half = (left + right) / 2;
        }
        else
        {
            // left == half == right
            (*diff_start) = -1;
            find_diff_range(nums, left, half, diff_start, diff_end);
            if ((*diff_start) != -1)
            {
                left = (*diff_start);
                right = (*diff_end);
                half = (left + right) / 2;
            }
            else
            {
                left = half;
                half = (left + right) / 2;
            }
        }
    }
    return fmin(nums[left], nums[right]);
}
// @lc code=end
