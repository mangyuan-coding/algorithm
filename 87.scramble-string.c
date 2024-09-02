/*
 * @lc app=leetcode.cn id=87 lang=c
 *
 * [87] Scramble String
 *
 * https://leetcode.cn/problems/scramble-string/description/
 *
 * algorithms
 * Hard (47.05%)
 * Likes:    573
 * Dislikes: 0
 * Total Accepted:    64.9K
 * Total Submissions: 137.9K
 * Testcase Example:  '"great"\n"rgeat"'
 *
 * We can scramble a string s to get a string t using the following
 * algorithm:
 *
 *
 * If the length of the string is 1, stop.
 * If the length of the string is > 1, do the following:
 *
 * Split the string into two non-empty substrings at a random index, i.e., if
 * the string is s, divide it to x and y where s = x + y.
 * Randomly decide to swap the two substrings or to keep them in the same
 * order. i.e., after this step, s may become s = x + y or s = y + x.
 * Apply step 1 recursively on each of the two substrings x and y.
 *
 *
 *
 *
 * Given two strings s1 and s2 of the same length, return true if s2 is a
 * scrambled string of s1, otherwise, return false.
 *
 *
 * Example 1:
 *
 *
 * Input: s1 = "great", s2 = "rgeat"
 * Output: true
 * Explanation: One possible scenario applied on s1 is:
 * "great" --> "gr/eat" // divide at random index.
 * "gr/eat" --> "gr/eat" // random decision is not to swap the two substrings
 * and keep them in order.
 * "gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both
 * substrings. divide at random index each of them.
 * "g/r / e/at" --> "r/g / e/at" // random decision was to swap the first
 * substring and to keep the second substring in the same order.
 * "r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively,
 * divide "at" to "a/t".
 * "r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both
 * substrings in the same order.
 * The algorithm stops now, and the result string is "rgeat" which is s2.
 * As one possible scenario led s1 to be scrambled to s2, we return true.
 *
 *
 * Example 2:
 *
 *
 * Input: s1 = "abcde", s2 = "caebd"
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input: s1 = "a", s2 = "a"
 * Output: true
 *
 *
 *
 * Constraints:
 *
 *
 * s1.length == s2.length
 * 1 <= s1.length <= 30
 * s1 and s2 consist of lowercase English letters.
 *
 *
 */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// @lc code=start
const int CHAR_SIZE = 26;

bool contain_same_chars(char *origin, int o_start, int o_end,
                        char *dest, int d_start, int d_end)
{
    int *char_size = calloc(CHAR_SIZE, sizeof(int));
    int sizes = 0;
    for (int i = o_start; i <= o_end; i++)
    {
        char_size[origin[i] - 'a']++;
    }
    for (int i = d_start; i <= d_end; i++)
    {
        if (char_size[dest[i] - 'a'] == 0)
        {
            return false;
        }
        char_size[dest[i] - 'a']--;
    }
    return true;
}

bool sub_is_scramble(char *origin, int o_start, int o_end,
                     char *dest, int d_start, int d_end,
                     int **record, int len)
{
    if (record[o_start * len + o_end][d_start * len + d_end] != 0)
    {
        return record[o_start * len + o_end][d_start * len + d_end] == 1;
    }
    if (o_start == o_end)
    {
        record[o_start * len + o_end][d_start * len + d_end] = origin[o_start] == dest[d_start];
        return origin[o_start] == dest[d_start];
    }
    if (!contain_same_chars(origin, o_start, o_end, dest, d_start, d_end))
    {
        record[o_start * len + o_end][d_start * len + d_end] = -1;
        return false;
    }
    for (int l_size = 1; l_size <= o_end - o_start; l_size++)
    {
        // same destination
        bool left = false, right = false;
        if (record[o_start * len + o_start + l_size - 1][d_start * len + d_start + l_size - 1] == 0)
        {
            left = sub_is_scramble(origin, o_start, o_start + l_size - 1, dest, d_start, d_start + l_size - 1, record, len);
        }
        else
        {
            left = record[o_start * len + o_start + l_size - 1][d_start * len + d_start + l_size - 1] == 1;
        }
        if (left)
        {
            if (record[(o_start + l_size) * len + o_end][(d_start + l_size) * len + d_end] == 0)
            {
                right = sub_is_scramble(origin, o_start + l_size, o_end, dest, d_start + l_size, d_end, record, len);
            }
            else
            {
                right = record[(o_start + l_size) * len + o_end][(d_start + l_size) * len + d_end] == 1;
            }
            if (right)
            {
                record[o_start * len + o_end][d_start * len + d_end] = true;
                return true;
            }
        }

        // diff destination
        left = false, right = false;
        if (record[o_start * len + o_start + l_size - 1][(d_end - l_size + 1) * len + d_end] == 0)
        {
            left = sub_is_scramble(origin, o_start, o_start + l_size - 1, dest, d_end - l_size + 1, d_end, record, len);
        }
        else
        {
            left = record[o_start * len + o_start + l_size - 1][(d_end - l_size + 1) * len + d_end] == 1;
        }
        if (left)
        {
            if (record[(o_start + l_size) * len + o_end][d_start * len + d_end - l_size] == 0)
            {
                right = sub_is_scramble(origin, o_start + l_size, o_end, dest, d_start, d_end - l_size, record, len);
            }
            else
            {
                right = record[(o_start + l_size) * len + o_end][d_start * len + d_end - l_size] == 1;
            }
            if (right)
            {
                record[o_start * len + o_end][d_start * len + d_end] = true;
                return true;
            }
        }
    }

    record[o_start * len + o_end][d_start * len + d_end] = -1;
    return false;
}

bool isScramble(char *s1, char *s2)
{
    int len = strlen(s1);
    if (len == 1)
    {
        return s1[0] == s2[0];
    }

    int idx_size = len * len;
    int **record = malloc(sizeof(int *) * idx_size);
    for (int i = 0; i < idx_size; i++)
    {
        record[i] = calloc(idx_size, sizeof(int *));
    }

    return sub_is_scramble(s1, 0, len - 1, s2, 0, len - 1, record, len);
}
// @lc code=end
int main(int argc, char const *argv[])
{

    bool is = isScramble("abcd", "bcad");
    return 0;
}
