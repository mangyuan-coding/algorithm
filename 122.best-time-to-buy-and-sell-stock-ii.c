/*
 * @lc app=leetcode.cn id=122 lang=c
 *
 * [122] Best Time to Buy and Sell Stock II
 */

// @lc code=start
#include <stdlib.h>

int maxProfit(int *prices, int pricesSize)
{
    // f(0, 1) = p[1] - p[0] > 0 ? p[1] - p[0] : 0
    // f(1, 2) = p[2] - p[1] > 0 ? p[2] - p[1] : 0
    // f(2, 3) = p[3] - p[2] > 0 ? p[3] - p[2] : 0
    // f(0, 2) = max(f(0, 1) + f(1, 2), p[2] - p[0] > 0 ? p[2] - p[0] : 0)
    // f(1, 3) = max(f(1, 2) + f(2, 3), p[3] - p[1] > 0 ? p[3] - p[1] : 0)
    // f(0, 3) = max(f(0, 1) + f(1, 2) + f(2, 3), f(0, 2) + f(2, 3), f(0, 1) + f(1, 3), p[3] - p[0] > 0 ? p[3] - p[0] : 0)
    // f(0, 1) + f(1, 2) + f(2, 3)
    // prove f(0, 1) + f(1, 2) + f(2, 3) <= f(0, 2) + f(2, 3)
    // namely f(0, 1) + f(1, 2) <= f(0, 2)
    // cause f(0, 2) = max(f(0, 1) + f(1, 2), p[2] - p[0] > 0 ? p[2] - p[0] : 0)
    // so f(0, 2) >= f(0, 1) + f(1, 2)
    // deduce when i < j f(i, j) >= f(i, j - 1) + f(j - i, j)
    // deduce f(0, n) = max(f(0, n - 1) + f(n - 1, n), p[0] - p[n])
    int pre_profit = 0;
    for (int i = 1; i < pricesSize; i++)
    {
        if (prices[i] - prices[i - 1] > 0)
        {
            pre_profit += prices[i] - prices[i - 1];
        }
    }
    return pre_profit;
}
// @lc code=end
