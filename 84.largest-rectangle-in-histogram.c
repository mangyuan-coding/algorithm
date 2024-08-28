/*
 * @lc app=leetcode.cn id=84 lang=c
 *
 * [84] Largest Rectangle in Histogram
 *
 * https://leetcode.cn/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (46.14%)
 * Likes:    2778
 * Dislikes: 0
 * Total Accepted:    443K
 * Total Submissions: 960K
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 * Given an array of integers heights representing the histogram's bar height
 * where the width of each bar is 1, return the area of the largest rectangle
 * in the histogram.
 *
 *
 * Example 1:
 *
 *
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10
 * Explanation: The above is a histogram where width of each bar is 1.
 * The largest rectangle is shown in the red area, which has an area = 10
 * units.
 *
 *
 * Example 2:
 *
 *
 * Input: heights = [2,4]
 * Output: 4
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= heights.length <= 10^5
 * 0 <= heights[i] <= 10^4
 *
 *
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// @lc code=start
int largestRectangleArea(int *heights, int heightsSize)
{
    if (heightsSize == 1)
    {
        return heights[0];
    }

    int *left_incr_stack = malloc(sizeof(int) * (heightsSize + 1));
    int left_incr_stack_size = 0;
    int *right_incr_stack = malloc(sizeof(int) * (heightsSize + 1));
    int right_incr_stack_size = 0;

    int *left_min_idx = malloc(sizeof(int) * heightsSize);
    int *right_min_idx = malloc(sizeof(int) * heightsSize);
    for (int step = 0; step < heightsSize; step++)
    {
        while (left_incr_stack_size > 0 && heights[left_incr_stack[left_incr_stack_size - 1]] >= heights[step])
        {
            left_incr_stack_size--;
        }
        left_min_idx[step] = left_incr_stack_size == 0 ? -1 : left_incr_stack[left_incr_stack_size - 1];
        left_incr_stack[left_incr_stack_size++] = step;
        while (right_incr_stack_size > 0 && heights[right_incr_stack[right_incr_stack_size - 1]] >= heights[heightsSize - step - 1])
        {
            right_incr_stack_size--;
        }
        right_min_idx[heightsSize - step - 1] = right_incr_stack_size == 0 ? heightsSize : right_incr_stack[right_incr_stack_size - 1];
        right_incr_stack[right_incr_stack_size++] = heightsSize - step - 1;
    }

    int max_area = 0;
    for (int i = 0; i < heightsSize; i++)
    {
        max_area = fmax(max_area, (right_min_idx[i] - left_min_idx[i] - 1) * heights[i]);
    }

    return max_area;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int height[6] = {2, 1, 5, 6, 2, 3};
    largestRectangleArea(height, 6);
    return 0;
}
