/*
 * @lc app=leetcode.cn id=115 lang=c
 *
 * [115] Distinct Subsequences
 *
 * https://leetcode.cn/problems/distinct-subsequences/description/
 *
 * algorithms
 * Hard (52.35%)
 * Likes:    1264
 * Dislikes: 0
 * Total Accepted:    192K
 * Total Submissions: 366.8K
 * Testcase Example:  '"rabbbit"\n"rabbit"'
 *
 * Given two strings s and t, return the number of distinct subsequences of s
 * which equals t.
 *
 * The test cases are generated so that the answer fits on a 32-bit signed
 * integer.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "rabbbit", t = "rabbit"
 * Output: 3
 * Explanation:
 * As shown below, there are 3 ways you can generate "rabbit" from s.
 * rabbbit
 * rabbbit
 * rabbbit
 *
 *
 * Example 2:
 *
 *
 * Input: s = "babgbag", t = "bag"
 * Output: 5
 * Explanation:
 * As shown below, there are 5 ways you can generate "bag" from s.
 * babgbag
 * babgbag
 * babgbag
 * babgbag
 * babgbag
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length, t.length <= 1000
 * s and t consist of English letters.
 *
 *
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>

// @lc code=start

int numDistinct(char *s, char *t)
{
    int s_len = strlen(s);
    int t_len = strlen(t);
    if (t_len > s_len)
    {
        return 0;
    }
    unsigned int **record = malloc(sizeof(int *) * s_len);
    for (int i = 0; i < s_len; i++)
    {
        record[i] = calloc(t_len, sizeof(int));
    }

    record[0][0] = s[0] == t[0] ? 1 : 0;
    for (int i = 1; i < s_len; i++)
    {
        for (int j = 0; j < fmin(i + 1, t_len); j++)
        {
            record[i][j] = record[i - 1][j];
            if (s[i] == t[j])
            {
                if (j == 0)
                {
                    record[i][j] += 1;
                }
                else
                {
                    record[i][j] += record[i - 1][j - 1];
                }
            }
        }
    }

    return record[s_len - 1][t_len - 1];
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int distinct = numDistinct("rabbbit", "rabbit");
    return 0;
}
