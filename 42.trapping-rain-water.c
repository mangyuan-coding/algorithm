/*
 * @lc app=leetcode.cn id=42 lang=c
 *
 * [42] Trapping Rain Water
 *
 * https://leetcode.cn/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (64.00%)
 * Likes:    5261
 * Dislikes: 0
 * Total Accepted:    1M
 * Total Submissions: 1.6M
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 *
 *
 * Example 1:
 *
 *
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue
 * section) are being trapped.
 *
 *
 * Example 2:
 *
 *
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *
 *
 *
 * Constraints:
 *
 *
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
 *
 *
 */

#include <stdbool.h>
#include <math.h>

// @lc code=start

int find_range_top_peak_idx(int *height, int start, int end)
{
    int top = 0, top_idx;
    for (int i = start; i <= end; i++)
    {
        if (height[i] >= top)
        {
            top = height[i];
            top_idx = i;
        }
    }
    return top_idx;
}

int find_range_top_peak_idx_from_left(int *height, int start, int end)
{
    int top = 0, top_idx = -1;
    bool has_valley = false;
    for (int i = start; i <= end; i++)
    {
        if (has_valley)
        {
            if (height[i] >= top)
            {
                top = height[i];
                top_idx = i;
            }
        }
        else
        {
            if (i == end)
            {
                break;
            }
            else if (height[i] < height[i + 1])
            {
                has_valley = true;
            }
        }
    }
    return top_idx;
}

int find_range_top_peak_idx_from_right(int *height, int start, int end)
{
    int top = 0, top_idx = -1;
    bool has_valley = false;
    for (int i = end; i >= start; i--)
    {
        if (has_valley)
        {
            if (height[i] >= top)
            {
                top = height[i];
                top_idx = i;
            }
        }
        else
        {
            if (i == start)
            {
                break;
            }
            else if (height[i] < height[i - 1])
            {
                has_valley = true;
            }
        }
    }
    return top_idx;
}

int trap_left(int *height, int start, int top_peak_idx)
{
    if (start >= top_peak_idx)
    {
        return 0;
    }
    int left_top_peak_idx = find_range_top_peak_idx_from_right(height, start, top_peak_idx - 1);
    if (left_top_peak_idx == -1)
    {
        return 0;
    }

    int volume = 0;

    for (int i = left_top_peak_idx + 1; i < top_peak_idx; i++)
    {
        if (height[left_top_peak_idx] > height[i])
        {
            volume += (height[left_top_peak_idx] - height[i]);
        }
    }

    return volume + trap_left(height, start, left_top_peak_idx);
}
int trap_right(int *height, int top_peak_idx, int end)
{
    if (top_peak_idx >= end)
    {
        return 0;
    }

    int right_top_peak_idx = find_range_top_peak_idx_from_left(height, top_peak_idx + 1, end);
    if (right_top_peak_idx == -1)
    {
        return 0;
    }

    int volume = 0;

    for (int i = top_peak_idx + 1; i < right_top_peak_idx; i++)
    {
        if (height[right_top_peak_idx] > height[i])
        {
            volume += (height[right_top_peak_idx] - height[i]);
        }
    }

    return volume + trap_right(height, right_top_peak_idx, end);
}

int trap(int *height, int heightSize)
{
    if (heightSize <= 2)
    {
        return 0;
    }

    int peak_idx = find_range_top_peak_idx(height, 0, heightSize - 1);
    return trap_left(height, 0, peak_idx) + trap_right(height, peak_idx, heightSize - 1);
}
// @lc code=end
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int heightSize = 4;
    int *height = malloc(sizeof(int) * heightSize);
    height[0] = 5;
    height[1] = 4;
    height[2] = 1;
    height[3] = 2;
    // height[4] = 1;
    // height[5] = 0;
    // height[6] = 1;
    // height[7] = 3;
    // height[8] = 2;
    // height[9] = 1;
    // height[10] = 2;
    // height[11] = 1;
    int volume = trap(height, heightSize);
    return 0;
}