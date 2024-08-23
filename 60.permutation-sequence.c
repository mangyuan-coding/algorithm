/*
 * @lc app=leetcode.cn id=60 lang=c
 *
 * [60] Permutation Sequence
 *
 * https://leetcode.cn/problems/permutation-sequence/description/
 *
 * algorithms
 * Hard (53.83%)
 * Likes:    849
 * Dislikes: 0
 * Total Accepted:    145K
 * Total Submissions: 269.4K
 * Testcase Example:  '3\n3'
 *
 * The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
 *
 * By listing and labeling all of the permutations in order, we get the
 * following sequence for n = 3:
 *
 *
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 *
 *
 * Given n and k, return the k^th permutation sequence.
 *
 *
 * Example 1:
 * Input: n = 3, k = 3
 * Output: "213"
 * Example 2:
 * Input: n = 4, k = 9
 * Output: "2314"
 * Example 3:
 * Input: n = 3, k = 1
 * Output: "123"
 *
 *
 * Constraints:
 *
 *
 * 1 <= n <= 9
 * 1 <= k <= n!
 *
 *
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// @lc code=start
char *getPermutation(int n, int k)
{
    if (n == 1)
    {
        return "1";
    }

    char *permutation = malloc(sizeof(char) * (n + 2));
    int *factorials = malloc(sizeof(int) * n);
    for (int i = 1; i <= n; i++)
    {
        permutation[i] = '0' + i;
        if (i == 1)
        {
            factorials[0] = 1;
        }
        else
        {
            factorials[i - 1] = factorials[i - 2] * i;
        }
    }
    permutation[n + 1] = '\0';

    for (int idx = 0; idx < n; idx++)
    {
        if (k == 0)
        {
            int step = (n - idx) / 2;
            for (int i = 0; i < step; i++)
            {
                permutation[idx + i] = permutation[n - i];
                permutation[n - i] = permutation[idx + i + 1];
            }
            idx = idx + step;
            for (; idx <= n; idx++)
            {
                permutation[idx] = permutation[idx + 1];
            }
            break;
        }
        else if (k == 1)
        {
            permutation[idx] = permutation[idx + 1];
        }
        else
        {
            int factorial = factorials[n - idx - 2];
            int char_idx;
            if (k % factorial == 0)
            {
                char_idx = idx + k / factorial;
            }
            else
            {
                char_idx = idx + k / factorial + 1;
            }
            permutation[idx] = permutation[char_idx];
            for (int i = char_idx; i > idx + 1; i--)
            {
                permutation[i] = permutation[i - 1];
            }
            k = k % factorials[n - idx - 2];
        }
    }
    permutation[n] = '\0';

    return permutation;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%s", getPermutation(2, 2));
    return 0;
}
