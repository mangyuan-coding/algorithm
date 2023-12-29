/*
 * @lc app=leetcode id=70 lang=c
 *
 * [70] Climbing Stairs
 */

// @lc code=start
#include <stdlib.h>

int climbStairs(int n)
{
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 2;
    }

    int pre_pre = 1, pre = 2, cur;
    for (int i = 2; i < n; i++)
    {
        cur = pre_pre + pre;
        pre_pre = pre;
        pre = cur;
    }
    return cur;
}
// @lc code=end
