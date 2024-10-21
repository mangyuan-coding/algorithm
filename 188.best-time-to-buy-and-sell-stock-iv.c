/*
 * @lc app=leetcode.cn id=188 lang=c
 *
 * [188] Best Time to Buy and Sell Stock IV
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/description/
 *
 * algorithms
 * Hard (51.14%)
 * Likes:    1210
 * Dislikes: 0
 * Total Accepted:    286K
 * Total Submissions: 559.2K
 * Testcase Example:  '2\n[2,4,1]'
 *
 * You are given an integer array prices where prices[i] is the price of a
 * given stock on the i^th day, and an integer k.
 *
 * Find the maximum profit you can achieve. You may complete at most k
 * transactions: i.e. you may buy at most k times and sell at most k times.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 *
 *
 * Example 1:
 *
 *
 * Input: k = 2, prices = [2,4,1]
 * Output: 2
 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit
 * = 4-2 = 2.
 *
 *
 * Example 2:
 *
 *
 * Input: k = 2, prices = [3,2,6,5,0,3]
 * Output: 7
 * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit
 * = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3),
 * profit = 3-0 = 3.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= k <= 100
 * 1 <= prices.length <= 1000
 * 0 <= prices[i] <= 1000
 *
 *
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// @lc code=start

int maxProfit(int k, int *prices, int pricesSize)
{
    if (pricesSize == 1)
    {
        return 0;
    }
    if (pricesSize == 2)
    {
        return fmax(prices[1] - prices[0], 0);
    }

    int max_trans = fmin(k, pricesSize / 2);
    int hold[max_trans + 1], empty[max_trans + 1];

    memset(hold, 0, sizeof(hold));
    memset(empty, 0, sizeof(empty));

    hold[0] = -prices[0];
    empty[0] = 0;

    for (int i = 1; i <= max_trans; i++)
    {
        hold[i] = empty[i] = INT32_MIN / 2;
    }

    for (int i = 1; i < pricesSize; ++i)
    {
        hold[0] = fmax(hold[0], empty[0] - prices[i]);
        for (int j = 1; j <= max_trans; ++j)
        {
            hold[j] = fmax(hold[j], empty[j] - prices[i]);
            empty[j] = fmax(empty[j], hold[j - 1] + prices[i]);
        }
    }
    int max_profit = 0;
    for (int i = 0; i <= max_trans; i++)
    {
        max_profit = fmax(max_profit, empty[i]);
    }

    return max_profit;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int k = 2;
    int prices[3] = {2, 4, 1};
    int pricesSize = 3;
    int max_profit = maxProfit(k, prices, pricesSize);
    return 0;
}
