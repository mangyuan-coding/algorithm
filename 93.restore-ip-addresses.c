/*
 * @lc app=leetcode id=93 lang=c
 *
 * [93] Restore IP Addresses
 */
#include <stdio.h>
// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <string.h>
#include <stdlib.h>

char **restoreIpAddresses(char *s, int *returnSize)
{
    *returnSize = 0;
    int len = strlen(s);
    if (len < 4 || len > 12)
    {
        return NULL;
    }

    // define
    char **ips = (char **)malloc(sizeof(char *) * 81);
    int *trace = (int *)malloc(sizeof(int) * 4);
    int trace_idx = 0, cur_used_size = 0, remain_size, cur_num;

    // init
    trace[trace_idx] = 1;
    cur_used_size = 1;
    trace_idx++;

    // loop
    while (1)
    {
        if (trace_idx < 3)
        {
            trace[trace_idx] = 1;
            cur_used_size += 1;
            trace_idx++;
        }
        else
        // trace_idx = 3
        {
            remain_size = len - cur_used_size;
            if (remain_size > 0 && remain_size <= 3 && (s[cur_used_size] != '0' || remain_size == 1))
            {
                trace[trace_idx] = remain_size;
                cur_num = 0;
                for (int i = cur_used_size; i < len; i++)
                {
                    cur_num = cur_num * 10 + (s[i] - '0');
                }
                if (cur_num >= 0 && cur_num <= 255)
                {

                    (*returnSize)++;
                    ips[*returnSize - 1] = (char *)malloc(sizeof(char) * (len + 4));

                    memcpy(ips[*returnSize - 1], s, sizeof(char) * trace[0]);
                    ips[*returnSize - 1][trace[0]] = '.';
                    memcpy(ips[*returnSize - 1] + trace[0] + 1, s + trace[0], sizeof(char) * trace[1]);
                    ips[*returnSize - 1][trace[0] + trace[1] + 1] = '.';
                    memcpy(ips[*returnSize - 1] + trace[0] + trace[1] + 2, s + trace[0] + trace[1], sizeof(char) * trace[2]);
                    ips[*returnSize - 1][trace[0] + trace[1] + trace[2] + 2] = '.';
                    memcpy(ips[*returnSize - 1] + trace[0] + trace[1] + trace[2] + 3, s + trace[0] + trace[1] + trace[2], sizeof(char) * trace[3]);

                    ips[*returnSize - 1][len + 3] = '\0';
                }
            }
            // back
            trace_idx--;
            while (trace_idx >= 0)
            {
                if (trace[trace_idx] <= 2 && cur_used_size + 1 < len && s[cur_used_size - trace[trace_idx]] != '0')
                {
                    cur_num = 0;
                    for (int i = cur_used_size - trace[trace_idx]; i < cur_used_size + 1; i++)
                    {
                        cur_num = cur_num * 10 + (s[i] - '0');
                    }
                    if (cur_num >= 0 && cur_num <= 255)
                    {
                        break;
                    }
                }
                cur_used_size -= trace[trace_idx];
                trace_idx--;
            }
            if (trace_idx < 0)
            {
                break;
            }
            trace[trace_idx]++;
            cur_used_size++;
            trace_idx++;
        }
    }
    return ips;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int *returnSize = (int *)malloc(sizeof(int));
    char **ips = restoreIpAddresses("101023", returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%s ", ips[i]);
    }
    return 0;
}
