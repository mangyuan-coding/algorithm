/*
 * @lc app=leetcode id=13 lang=c
 *
 * [13] Roman to Integer
 */

// @lc code=start
#include <string.h>

const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

int romanToInt(char *s)
{
    int ret = 0;
    int index = 0;
    for (int i = 0; i < 13; i++)
    {
        const char *symbol = symbols[i];
        int len = strlen(symbols[i]);
        while (!strncmp(s + index, symbols[i], len))
        {
            ret += values[i];
            index += len;
        }
    }
    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("ret is %d", romanToInt("III"));
    return 0;
}
