/*
 * @lc app=leetcode id=20 lang=c
 *
 * [20] Valid Parentheses
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isValid(char *s)
{
    int len = strlen(s);
    if (len % 2 == 1)
    {
        return false;
    }
    char *trace = (char *)malloc(sizeof(char) * len);
    int trace_idx = 0;

    for (int i = 0; i < len; i++)
    {
        switch (s[i])
        {
        case '(':
        case '[':
        case '{':
            trace[trace_idx++] = s[i];
            break;
        case ')':
            if (trace_idx < 1 || trace[trace_idx - 1] != '(')
            {
                return false;
            }
            trace_idx--;
            break;
        case ']':
            if (trace_idx < 1 || trace[trace_idx - 1] != '[')
            {
                return false;
            }
            trace_idx--;
            break;
        case '}':
            if (trace_idx < 1 || trace[trace_idx - 1] != '{')
            {
                return false;
            }
            trace_idx--;
            break;
        default:
            break;
        }
    }
    return trace_idx == 0 ? true : false;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("parentheses is %d \n", isValid("(("));
    return 0;
}
