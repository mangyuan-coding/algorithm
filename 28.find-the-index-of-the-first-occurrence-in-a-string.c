/*
 * @lc app=leetcode id=28 lang=c
 *
 * [28] Find the Index of the First Occurrence in a String
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>

int strStr(char *haystack, char *needle)
{
    int len = strlen(haystack);
    int nee_len = strlen(needle);

    for (int i = 0; i < len - nee_len + 1; i++)
    {
        if (haystack[i] == needle[0])
        {
            bool hit = true;
            for (int j = 1; j < nee_len; j++)
            {
                if (haystack[i + j] != needle[j])
                {
                    hit = false;
                    break;
                }
            }
            if (hit)
            {
                return i;
            }
        }
    }

    return -1;
}
// @lc code=end
