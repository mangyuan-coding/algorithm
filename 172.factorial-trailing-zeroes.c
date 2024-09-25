/*
 * @lc app=leetcode.cn id=172 lang=c
 *
 * [172] Factorial Trailing Zeroes
 *
 * https://leetcode.cn/problems/factorial-trailing-zeroes/description/
 *
 * algorithms
 * Medium (50.58%)
 * Likes:    850
 * Dislikes: 0
 * Total Accepted:    210.4K
 * Total Submissions: 415.9K
 * Testcase Example:  '3'
 *
 * Given an integer n, return the number of trailing zeroes in n!.
 *
 * Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.
 *
 *
 * Example 1:
 *
 *
 * Input: n = 3
 * Output: 0
 * Explanation: 3! = 6, no trailing zero.
 *
 *
 * Example 2:
 *
 *
 * Input: n = 5
 * Output: 1
 * Explanation: 5! = 120, one trailing zero.
 *
 *
 * Example 3:
 *
 *
 * Input: n = 0
 * Output: 0
 *
 *
 *
 * Constraints:
 *
 *
 * 0 <= n <= 10^4
 *
 *
 *
 * Follow up: Could you write a solution that works in logarithmic time
 * complexity?
 *
 */

// @lc code=start
int trailingZeroes(int n)
{
    int zeroes = 0;

    while (n)
    {
        n /= 5;
        zeroes += n;
    }

    return zeroes;
}
// @lc code=end
