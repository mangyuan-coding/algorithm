/*
 * @lc app=leetcode id=38 lang=c
 *
 * [38] Count and Say
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

char *countAndSay(int n)
{
    char *last = malloc(sizeof(char) * 2), *curret;
    last[0] = '1';
    last[1] = '\0';
    for (int i = 2; i <= n; i++)
    {
        int len = strlen(last);

        curret = malloc(sizeof(char) * len * 2 + 1);
        int index = 0;

        int count = 1;
        for (int j = 1; j < len; j++)
        {
            if (last[j] == last[j - 1])
            {
                count++;
            }
            else
            {
                curret[index++] = count + '0';
                curret[index++] = last[j - 1];
                count = 1;
            }
        }
        curret[index++] = count + '0';
        curret[index++] = last[len - 1];
        curret[index++] = '\0';
        free(last);
        last = curret;
    }
    return last;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // printf("resut is %s \n", countAndSay(1));
    // printf("resut is %s \n", countAndSay(2));
    // printf("resut is %s \n", countAndSay(3));
    // printf("resut is %s \n", countAndSay(4));
    // printf("resut is %s \n", countAndSay(5));
    printf("resut is %s \n", countAndSay(6));
    return 0;
}
