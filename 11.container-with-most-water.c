/*
 * @lc app=leetcode id=11 lang=c
 *
 * [11] Container With Most Water
 */

// @lc code=start
#include <math.h>

// int maxArea_idx(int *height, int left, int right)
// {
//     if (left + 1 == right)
//     {
//         return fmin(height[left], height[right]);
//     }

//     int area = fmin(height[left], height[right]) * (right - left);

//     return fmax(fmax(maxArea_idx(height, left, right - 1), maxArea_idx(height, left + 1, right)), area);
// }

// int maxArea(int *height, int heightSize)
// {
//     if (heightSize <= 1)
//     {
//         return 0;
//     }
//     return maxArea_idx(height, 0, heightSize - 1);
// }

int maxArea(int *height, int heightSize)
{
    if (heightSize <= 1)
    {
        return 0;
    }

    int max_area = 0;
    for (int i = 0; i < heightSize; i++)
    {
        for (int j = i + 1; j < heightSize; j++)
        {
            int area = fmin(height[i], height[j]) * (j - i);
            if (max_area < area)
            {
                max_area = area;
            }
        }
    }

    return max_area;
}

// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{

    int height[] = {1, 2, 3, 4, 5};
    printf("max-area is %d", maxArea(height, 4));
    return 0;
}
