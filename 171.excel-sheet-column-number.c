/*
 * @lc app=leetcode id=171 lang=c
 *
 * [171] Excel Sheet Column Number
 */

// @lc code=start
#include <string.h>
#include <math.h>

int titleToNumber(char *columnTitle)
{
    int len = strlen(columnTitle);
    int num = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        num += (columnTitle[i] - 'A' + 1) * pow(26, len - i - 1);
    }
    return num;
}
// @lc code=end
