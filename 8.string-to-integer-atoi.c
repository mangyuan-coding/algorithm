/*
 * @lc app=leetcode id=8 lang=c
 *
 * [8] String to Integer (atoi)
 */

// @lc code=start
#include <string.h>
#include <stdint.h>

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
    int positive = 1;

    while (num_l < len && num_r < len)
    {
        /* code */
        if (s[num_l] == ' ')
        {
            num_l++;
            continue;
        }
        if (s[num_l] == '+' || s[num_l] == '-')
        {
            positive = s[num_l] == '-' ? 0 : 1;
            num_l++;
            continue;
        }
    }

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("ret is %d", myAtoi("3.14159"));
    return 0;
}
