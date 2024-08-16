/*
 * @lc app=leetcode.cn id=32 lang=c
 *
 * [32] Longest Valid Parentheses
 *
 * https://leetcode.cn/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (38.30%)
 * Likes:    2547
 * Dislikes: 0
 * Total Accepted:    472K
 * Total Submissions: 1.2M
 * Testcase Example:  '"(()"'
 *
 * Given a string containing just the characters '(' and ')', return the length
 * of the longest valid (well-formed) parentheses substring.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()".
 *
 *
 * Example 2:
 *
 *
 * Input: s = ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()".
 *
 *
 * Example 3:
 *
 *
 * Input: s = ""
 * Output: 0
 *
 *
 *
 * Constraints:
 *
 *
 * 0 <= s.length <= 3 * 10^4
 * s[i] is '(', or ')'.
 *
 *
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>

// @lc code=start
int longestValidParentheses(char *s)
{
    int len = strlen(s);
    if (len <= 1)
    {
        return 0;
    }

    int *right_left = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
    {
        right_left[i] = -1;
    }

    int max_duration = 0;
    int c_left, c_right;
    for (int i = 0; i < len - 1; i++)
    {
        // find ()
        if (s[i] == '(' && s[i + 1] == ')')
        {
            right_left[i + 1] = i;
            c_left = i, c_right = i + 1;

            if (c_left != 0 && right_left[c_left - 1] != -1)
            {
                c_left = right_left[c_left - 1];
            }

            for (; c_left - 1 >= 0;)
            {
                if (s[c_left - 1] == '(' && c_right + 1 <= len - 1 && s[c_right + 1] == ')')
                {
                    right_left[c_right + 1] = c_left - 1;
                    c_left--;
                    c_right++;
                }
                else
                {
                    if (c_left - 1 > 0 && right_left[c_left - 1] != -1)
                    {
                        c_left = right_left[c_left - 1];
                    }
                    else
                    {
                        break;
                    }
                }
            }
            max_duration = fmax(max_duration, c_right - c_left + 1);
        }
    }
    return max_duration;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%d", longestValidParentheses("()(())"));
    return 0;
}
