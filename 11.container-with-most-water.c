/*
 * @lc app=leetcode id=11 lang=c
 *
 * [11] Container With Most Water
 */

// @lc code=start
#include <math.h>

int maxArea(int *height, int heightSize)
{
    if (heightSize <= 1)
    {
        return 0;
    }

    int max_area = 0;
    int left = 0, right = heightSize - 1;
    while (left < right)
    {
        int area = fmin(height[left], height[right]) * (right - left);
        if (area > max_area)
        {
            max_area = area;
        }
        if (height[left] < height[right])
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return max_area;
}

// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{

    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    printf("max-area is %d", maxArea(height, 9));
    return 0;
}
