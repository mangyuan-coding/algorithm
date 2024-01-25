/*
 * @lc app=leetcode id=121 lang=c
 *
 * [121] Best Time to Buy and Sell Stock
 */

// @lc code=start
int maxProfit(int *prices, int pricesSize)
{
    int max_profit = 0, min_price = prices[0];
    for (int i = 1; i < pricesSize; i++)
    {
        if (prices[i] < min_price)
        {
            min_price = prices[i];
        }
        else
        {
            if (prices[i] - min_price > max_profit)
            {
                max_profit = prices[i] - min_price;
            }
        }
    }
    return max_profit;
}
// @lc code=end
