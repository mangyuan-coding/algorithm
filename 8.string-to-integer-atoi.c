/*
 * @lc app=leetcode id=8 lang=c
 *
 * [8] String to Integer (atoi)
 */

// @lc code=start
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int myAtoi(char *s)
{
    int len = strlen(s);
    if (len == 0)
    {
        return 0;
    }

    int num_l = 0;
    int num_r = 0;

    int ret = 0;
    bool has_set_positive = false;

    const int min_un_digit = -214748364;
    const int max_un_digit = 214748364;
    const int min_digit = 8;
    const int max_digit = 7;

    while (num_l < len)
    {
        /* code */
        if (s[num_l] == ' ')
        {
            num_l++;
            continue;
        }

        if (s[num_l] == '+' || s[num_l] == '-')
        {
            num_r = num_l + 1;
        }
        else if (s[num_l] <= '9' && s[num_l] >= '0')
        {
            num_r = num_l;
        }
        else
        {
            return 0;
        }

        break;
    }

    while (num_r < len)
    {
        if (s[num_r] == '0' && ret == 0)
        {
            num_r++;
            continue;
        }

        if (s[num_r] >= '0' && s[num_r] <= '9')
        {
            int digit = (s[num_r] - '0');

            if (ret < min_un_digit)
            {
                return INT32_MIN;
            }
            if (ret > max_un_digit)
            {
                return INT32_MAX;
            }

            if (ret == min_un_digit && digit >= min_digit)
            {
                return INT32_MIN;
            }
            if (ret == max_un_digit && digit >= max_digit)
            {
                return INT32_MAX;
            }

            if (has_set_positive)
            {
                ret = ret > 0 ? (10 * ret + digit) : (10 * ret - digit);
            }
            else
            {
                ret = s[num_l] == '-' ? -digit : digit;
                has_set_positive = true;
            }

            num_r++;
        }
        else
        {
            break;
        }
    }

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("ret is %d", myAtoi("-2147483647"));
    return 0;
}
