/*
 * @lc app=leetcode id=58 lang=c
 *
 * [58] Length of Last Word
 */

// @lc code=start
#include <string.h>

int lengthOfLastWord(char *s)
{
    int len = strlen(s);
    int i = len - 1, j;
    for (; i >= 0; i--)
    {
        if (s[i] == ' ')
        {
            continue;
        }
        for (j = i; j >= 0; j--)
        {
            if (s[j] == ' ')
            {
                break;
            }
        }
        break;
    }
    return i - j;
}
// @lc code=end
