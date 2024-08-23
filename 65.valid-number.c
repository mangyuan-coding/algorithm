/*
 * @lc app=leetcode.cn id=65 lang=c
 *
 * [65] Valid Number
 *
 * https://leetcode.cn/problems/valid-number/description/
 *
 * algorithms
 * Hard (27.75%)
 * Likes:    382
 * Dislikes: 0
 * Total Accepted:    74.9K
 * Total Submissions: 269.8K
 * Testcase Example:  '"0"'
 *
 * Given a string s, return whether s is a valid number.
 *
 * For example, all the following are valid numbers: "2", "0089", "-0.1",
 * "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93",
 * "-123.456e789", while the following are not valid numbers: "abc", "1a",
 * "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53".
 *
 * Formally, a valid number is defined using one of the following
 * definitions:
 *
 *
 * An integer number followed by an optional exponent.
 * A decimal number followed by an optional exponent.
 *
 *
 * An integer number is defined with an optional sign '-' or '+' followed by
 * digits.
 *
 * A decimal number is defined with an optional sign '-' or '+' followed by one
 * of the following definitions:
 *
 *
 * Digits followed by a dot '.'.
 * Digits followed by a dot '.' followed by digits.
 * A dot '.' followed by digits.
 *
 *
 * An exponent is defined with an exponent notation 'e' or 'E' followed by an
 * integer number.
 *
 * The digits are defined as one or more digits.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "0"
 *
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: s = "e"
 *
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input: s = "."
 *
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 20
 * s consists of only English letters (both uppercase and lowercase), digits
 * (0-9), plus '+', minus '-', or dot '.'.
 *
 *
 */

#include <stdbool.h>
#include <string.h>

// @lc code=start

bool isNumber(char *s)
{
    int len = strlen(s);
    if (len == 1)
    {
        return s[0] >= '0' && s[0] <= '9';
    }

    if (s[len - 1] == 'E' || s[len - 1] == 'e' ||
        s[len - 1] == '+' || s[len - 1] == '-')
    {
        return false;
    }

    bool num_is_dec = false;
    bool num_has_num = false;
    bool has_e = false;
    bool e_is_dec = false;

    int i = 0;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }

    for (; i < len; i++)
    {
        if (has_e)
        {
            if (s[i] == '+' || s[i] == '-')
            {
                return false;
            }
            else if (s[i] < '0' || s[i] > '9')
            {
                return false;
            }
        }
        else
        {
            if (s[i] == '+' || s[i] == '-')
            {
                return false;
            }
            else if (s[i] == 'E' || s[i] == 'e')
            {
                if (i == 0 || s[i - 1] == '+' || s[i - 1] == '-' || i == len - 1 || !num_has_num)
                {
                    return false;
                }
                has_e = true;
                if (s[i + 1] == '+' || s[i + 1] == '-')
                {
                    i++;
                }
            }
            else if (s[i] == '.')
            {
                if (num_is_dec ||
                    (i > 0 && (s[i - 1] == '+' || s[i - 1] == '-') && i == len - 1))
                {
                    return false;
                }
                num_is_dec = true;
            }
            else if (s[i] < '0' || s[i] > '9')
            {
                return false;
            }
            else
            {
                num_has_num = true;
            }
        }
    }

    return true;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    isNumber("e9");
    return 0;
}
