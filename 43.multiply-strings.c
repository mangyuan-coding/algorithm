/*
 * @lc app=leetcode id=43 lang=c
 *
 * [43] Multiply Strings
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>

char *rev(char *s)
{
    int len = strlen(s);
    char *ret = (char *)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
    {
        ret[len - i - 1] = s[i];
    }
    ret[len] = '\0';
    return ret;
}

char *multiply(char *num1, char *num2)
{
    int len_1 = strlen(num1), len_2 = strlen(num2);
    if (len_1 == 1 && num1[0] == '0' ||
        (len_2 == 1 && num2[0] == '0'))
    {
        return "0";
    }

    int base = 100;
    int ret_idx = 0;
    char *ret = (char *)malloc(sizeof(char) * base);
    for (int i = 0; i < base; i++)
    {
        ret[i] = '0';
    }

    int carry_idx = 0;
    for (int i = len_1 - 1; i >= 0; i--)
    {
        int num_1 = num1[i] - '0';
        ret_idx = len_1 - i - 1;
        for (int j = len_2 - 1; j >= 0; j--)
        {
            int num_2 = num2[j] - '0';
            int num_3 = ret[ret_idx] - '0';
            int num = num_1 * num_2 + num_3;

            ret[ret_idx] = num % 10 + '0';
            ret_idx++;
            if (ret_idx == base)
            {
                base *= 1.5;
                ret = (char *)realloc(ret, sizeof(char) * base);
                for (int i = ret_idx; i < base; i++)
                {
                    ret[i] = '0';
                }
            }
            if (num >= 10)
            {
                int carry = num / 10;
                carry_idx = ret_idx;
                while (carry > 0)
                {
                    num = carry + (ret[carry_idx] - '0');
                    ret[carry_idx] = num % 10 + '0';
                    carry_idx++;
                    if (carry_idx == base)
                    {
                        base *= 1.5;
                        ret = (char *)realloc(ret, sizeof(char) * base);
                        for (int i = carry_idx; i < base; i++)
                        {
                            ret[i] = '0';
                        }
                    }
                    if (num >= 10)
                    {
                        carry = num / 10;
                    }
                    else
                    {
                        carry = 0;
                    }
                }
            }
        }
    }
    if (carry_idx < ret_idx)
    {
        carry_idx = ret_idx;
    }
    if (carry_idx + 1 == base)
    {
        ret = (char *)realloc(ret, sizeof(char) * (base + 1));
    }

    ret[carry_idx++] = '\0';

    return rev(ret);
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%s", multiply("2", "3"));
    return 0;
}
