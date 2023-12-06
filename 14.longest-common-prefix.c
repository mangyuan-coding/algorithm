/*
 * @lc app=leetcode id=14 lang=c
 *
 * [14] Longest Common Prefix
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *longestCommonPrefix(char **strs, int strsSize)
{

    int i = 0;
    for (; i <= 200; i++)
    {
        bool same = true;
        if (strlen(strs[0]) < i + 1)
        {
            same = false;
            break;
        }
        for (int j = 1; j < strsSize; j++)
        {
            if (strlen(strs[j]) < i + 1 || strs[j][i] != strs[j - 1][i])
            {
                same = false;
                break;
            }
        }
        if (!same)
        {
            break;
        }
    }
    if (i == 0)
    {
        return "";
    }
    char *ret = malloc(sizeof(char) * (i + 1));
    ret[i] = '\0';
    strncpy(ret, strs[0], i);
    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *strs[] = {"flower", "flow", "flight"};
    printf("ret is %s", longestCommonPrefix(strs, 3));
    return 0;
}
