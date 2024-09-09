/*
 * @lc app=leetcode.cn id=123 lang=c
 *
 * [123] Best Time to Buy and Sell Stock III
 *
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/description/
 *
 * algorithms
 * Hard (61.11%)
 * Likes:    1738
 * Dislikes: 0
 * Total Accepted:    360.6K
 * Total Submissions: 590K
 * Testcase Example:  '[3,3,5,0,0,3,1,4]'
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the i^th day.
 *
 * Find the maximum profit you can achieve. You may complete at most two
 * transactions.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you
 * must sell the stock before you buy again).
 *
 *
 * Example 1:
 *
 *
 * Input: prices = [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit
 * = 3-0 = 3.
 * Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 =
 * 3.
 *
 * Example 2:
 *
 *
 * Input: prices = [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit
 * = 5-1 = 4.
 * Note that you cannot buy on day 1, buy on day 2 and sell them later, as you
 * are engaging multiple transactions at the same time. You must sell before
 * buying again.
 *
 *
 * Example 3:
 *
 *
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= prices.length <= 10^5
 * 0 <= prices[i] <= 10^5
 *
 *
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// @lc code=start
int maxProfit(int *prices, int pricesSize)
{
    int max_profit = 0;
    int left_min = prices[0];
    int *left_max_profit = calloc(pricesSize, sizeof(int));
    left_max_profit[0] = 0;
    for (int i = 1; i < pricesSize; i++)
    {
        if (prices[i] > left_min)
        {
            if (max_profit < prices[i] - left_min)
            {
                max_profit = prices[i] - left_min;
                left_max_profit[i] = max_profit;
            }
            else
            {
                left_max_profit[i] = left_max_profit[i - 1];
            }
        }
        else
        {
            left_min = prices[i];
            left_max_profit[i] = left_max_profit[i - 1];
        }
    }

    max_profit = 0;
    int *right_max_profit = calloc(pricesSize, sizeof(int));
    right_max_profit[pricesSize - 1] = 0;
    int right_max = prices[pricesSize - 1];
    for (int i = pricesSize - 2; i >= 0; i--)
    {
        if (prices[i] < right_max)
        {
            if (right_max - prices[i] > max_profit)
            {
                max_profit = right_max - prices[i];
                right_max_profit[i] = max_profit;
            }
            else
            {
                right_max_profit[i] = right_max_profit[i + 1];
            }
        }
        else
        {
            right_max = prices[i];
            right_max_profit[i] = right_max_profit[i + 1];
        }
    }

    for (int i = 1; i < pricesSize; i++)
    {
        max_profit = fmax(max_profit, left_max_profit[i - 1] + right_max_profit[i]);
    }

    return max_profit;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int prices[10] = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    int max_profit = maxProfit(prices, 10);
    return 0;
}
