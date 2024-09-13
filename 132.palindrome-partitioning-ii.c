/*
 * @lc app=leetcode.cn id=132 lang=c
 *
 * [132] Palindrome Partitioning II
 *
 * https://leetcode.cn/problems/palindrome-partitioning-ii/description/
 *
 * algorithms
 * Hard (49.82%)
 * Likes:    758
 * Dislikes: 0
 * Total Accepted:    92.2K
 * Total Submissions: 185.1K
 * Testcase Example:  '"aab"'
 *
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 *
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using
 * 1 cut.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "a"
 * Output: 0
 *
 *
 * Example 3:
 *
 *
 * Input: s = "ab"
 * Output: 1
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 2000
 * s consists of lowercase English letters only.
 *
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// @lc code=start

const int CHAR_SIZE = 26;

int minCut(char *s)
{
    int len = strlen(s);
    if (len == 1)
    {
        return 0;
    }
    if (len == 2)
    {
        return s[0] == s[1] ? 0 : 1;
    }

    bool **palindrome = calloc(len, sizeof(bool *));
    int *min_cut = calloc(len, sizeof(int));
    for (int i = 0; i < len; i++)
    {

        min_cut[i] = INT16_MAX;
        for (int j = i; j >= 0; j--)
        {
            if (palindrome[j] == NULL)
            {
                palindrome[j] = calloc(len, sizeof(bool));
            }
            if (i == j)
            {
                palindrome[j][i] = true;
            }
            else if (s[i] != s[j])
            {
                palindrome[j][i] = false;
            }
            else
            {
                if (i - j == 1)
                {
                    palindrome[j][i] = true;
                }
                else
                {
                    palindrome[j][i] = palindrome[j + 1][i - 1];
                }
            }
            if (palindrome[j][i] && j > 0)
            {
                min_cut[i] = fmin(min_cut[i], min_cut[j - 1] + 1);
            }
        }
        if (palindrome[0][i])
        {
            min_cut[i] = 0;
        }
    }

    return min_cut[len - 1];
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int min_cut = minCut("aab");
    return 0;
}
