/*
 * @lc app=leetcode id=11 lang=c
 *
 * [11] Container With Most Water
 */

// @lc code=start
#include <math.h>

// if h(l) < h(r) and l, r, h(n) ∈ N﹢
// then min(h(l), h(r - 1)) * (r - l - 1) < min(h(l), h(r)) * (r - l)
// prove:
// 1. case h(l) < h(r - 1) :
//    min(h(l), h(r - 1)) * (r - l - 1) = h(l) * (r - l - 1)
//    min(h(l), h(r)) * (r - l)         = h(l) * (r - l)
//    because r - l > r - l - 1
//    so h(l) * (r - l - 1) < h(l) * (r - l)
//    finish min(h(l), h(r - 1)) * (r - l - 1) < min(h(l), h(r)) * (r - l)
// 2. case h(l) > h(r - 1) :
//    h(r - 1) < h(l) < h(r)
//    min(h(l), h(r - 1)) * (r - l - 1) = h(r - 1) * (r - l - 1)
//    min(h(l), h(r)) * (r - l)         = h(l) * (r - l)
//    because h(r - 1) < h(l) and (r - l - 1) < (r - l)
//    so h(r - 1) * (r - l - 1) < h(l) * (r - l)
//    finish min(h(l), h(r - 1)) * (r - l - 1) < min(h(l), h(r)) * (r - l)
// 3. case h(l) = h(r - 1) :
//    same to case 1
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
