/*
 * @lc app=leetcode.cn id=151 lang=c
 *
 * [151] Reverse Words in a String
 */

#include <stdio.h>

// @lc code=start
#include <string.h>
#include <stdlib.h>

char *reverseWords(char *s)
{
    int len = strlen(s);
    if (len == 1)
    {
        return s[0] == ' ' ? NULL : s;
    }
    char *reversed = (char *)malloc(sizeof(char) * (len + 1));
    int reversed_size = 0;

    int start, end = len - 1;
    while (end > 0)
    {
        while (end >= 0 && s[end] == ' ')
        {
            end--;
        }
        if (end == -1)
        {
            break;
        }
        start = end - 1;
        while (start >= 0 && s[start] != ' ')
        {
            start--;
        }
        start++;
        memcpy(reversed + reversed_size, s + start, sizeof(char) * (end - start + 1));
        reversed_size += (end - start + 2);
        reversed[reversed_size - 1] = ' ';
        if (start == 0)
        {
            break;
        }
        end = start - 1;
    }
    reversed[reversed_size - 1] = '\0';
    return reversed;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    char *ret = reverseWords("the sky is blue");
    printf("%s", ret);
    return 0;
}
