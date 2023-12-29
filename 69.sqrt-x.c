/*
 * @lc app=leetcode id=69 lang=c
 *
 * [69] Sqrt(x)
 */

// @lc code=start
// 46340
// 0 <= x <= 2³¹ - 1
// 46340² = 2147395600
int mySqrt(int x)
{
    if (x <= 1)
    {
        return x;
    }
    if (x >= 2147395600)
    {
        return 46340;
    }
    int left = 1, right = 46340, half, square;
    while (left < right)
    {
        half = (left + right) / 2;
        if (half == left)
        {
            return half;
        }
        square = half * half;
        if (square == x)
        {
            return half;
        }
        else if (square > x)
        {
            right = half;
        }
        else
        {
            left = half;
        }
    }
    return left;
}
// @lc code=end
