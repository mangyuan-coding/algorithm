/*
 * @lc app=leetcode id=49 lang=c
 *
 * [49] Group Anagrams
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

const int MAX_STR_LEN = 100;

char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    int **same_size_idxs = (int **)malloc(sizeof(int *) * MAX_STR_LEN);
    int *same_size_size = (int *)malloc(sizeof(int) * MAX_STR_LEN);
    for (int i = 0; i < MAX_STR_LEN; i++)
    {
        same_size_idxs[i] = NULL;
        same_size_size[i] = 0;
    }

    char ***ret = (char ***)malloc(sizeof(char **) * strsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * strsSize);
    *returnSize = 0;

    bool has_empty = false;
    int max_str_len = 0;
    for (int i = 0; i < strsSize; i++)
    {
        int len = strlen(strs[i]);
        if (len == 0)
        {
            if (has_empty)
            {
                (*returnColumnSizes)[0]++;
                ret[0][(*returnColumnSizes)[0] - 1] = (char *)malloc(sizeof(char));
                ret[0][(*returnColumnSizes)[0] - 1][0] = '\0';
            }
            else
            {
                (*returnSize)++;
                (*returnColumnSizes)[0] = 1;
                ret[0] = (char **)malloc(sizeof(char *) * strsSize);
                ret[0][0] = (char *)malloc(sizeof(char));
                ret[0][0][0] = '\0';
                has_empty = true;
            }
            continue;
        }

        if (same_size_size[len - 1] == 0)
        {
            same_size_idxs[len - 1] = (int *)malloc(sizeof(int) * strsSize);
        }
        same_size_size[len - 1]++;
        same_size_idxs[len - 1][same_size_size[len - 1] - 1] = i;
        if (len > max_str_len)
        {
            max_str_len = len;
        }
    }

    int *char_size = (int *)malloc(sizeof(int) * 26);
    for (int i = 0; i < 26; i++)
    {
        char_size[i] = 0;
    }

    for (int len = 1; len <= max_str_len; len++)
    {
        if (same_size_size[len - 1] > 0)
        {
            if (same_size_size[len - 1] == 1)
            {
                (*returnSize)++;
                (*returnColumnSizes)[*returnSize - 1] = 1;
                ret[*returnSize - 1] = (char **)malloc(sizeof(char *));
                ret[*returnSize - 1][0] = (char *)malloc(sizeof(char) * (len + 1));
                memcpy(ret[*returnSize - 1][0], strs[same_size_idxs[len - 1][0]], sizeof(char) * len);
                ret[*returnSize - 1][0][len] = '\0';
            }
            else
            {
                int group_size = 0;
                int *group_flag = (int *)malloc(sizeof(int) * same_size_size[len - 1]);
                int **group_char_size = (int **)malloc(sizeof(int *) * same_size_size[len - 1]);
                int **group_idx = (int **)malloc(sizeof(int *) * same_size_size[len - 1]);
                int *group_idx_size = (int *)malloc(sizeof(int) * same_size_size[len - 1]);
                for (int idx_of_same_size_idx = 0; idx_of_same_size_idx < same_size_size[len - 1]; idx_of_same_size_idx++)
                {
                    int idx_of_str = same_size_idxs[len - 1][idx_of_same_size_idx];
                    char *str = strs[idx_of_str];
                    int char_flag = 0x0;

                    for (int idx_of_char = 0; idx_of_char < len; idx_of_char++)
                    {
                        int num = str[idx_of_char] - 'a' + 1;
                        char_flag = char_flag | (0x1 << num);
                        char_size[num - 1]++;
                    }

                    if (group_size == 0)
                    {
                        group_size++;
                        group_flag[group_size - 1] = char_flag;
                        group_char_size[group_size - 1] = (int *)malloc(sizeof(int) * 26);
                        memcpy(group_char_size[group_size - 1], char_size, sizeof(int) * 26);
                        group_idx[group_size - 1] = (int *)malloc(sizeof(int) * same_size_size[len - 1]);
                        group_idx_size[group_size - 1] = 1;
                        group_idx[group_size - 1][0] = idx_of_str;
                    }
                    else
                    {
                        int idx_of_group = 0;
                        for (; idx_of_group < group_size; idx_of_group++)
                        {
                            if (group_flag[idx_of_group] == char_flag)
                            {
                                bool same = true;
                                for (int idx_of_char_size = 0; idx_of_char_size < 26; idx_of_char_size++)
                                {
                                    if (group_char_size[idx_of_group][idx_of_char_size] != char_size[idx_of_char_size])
                                    {
                                        same = false;
                                        break;
                                    }
                                }
                                if (same)
                                {
                                    break;
                                }
                            }
                        }
                        if (idx_of_group < group_size)
                        {
                            group_idx_size[idx_of_group]++;
                            group_idx[idx_of_group][group_idx_size[idx_of_group] - 1] = idx_of_str;
                        }
                        else
                        {
                            group_size++;
                            group_flag[group_size - 1] = char_flag;
                            group_char_size[group_size - 1] = (int *)malloc(sizeof(int) * 26);
                            memcpy(group_char_size[group_size - 1], char_size, sizeof(int) * 26);
                            group_idx[group_size - 1] = (int *)malloc(sizeof(int) * same_size_size[len - 1]);
                            group_idx_size[group_size - 1] = 1;
                            group_idx[group_size - 1][0] = idx_of_str;
                        }
                    }
                    for (int i = 0; i < 26; i++)
                    {
                        char_size[i] = 0;
                    }
                }

                for (int idx_of_group = 0; idx_of_group < group_size; idx_of_group++)
                {
                    (*returnSize)++;
                    ret[*returnSize - 1] = (char **)malloc(sizeof(char *) * group_idx_size[idx_of_group]);
                    (*returnColumnSizes)[*returnSize - 1] = 0;
                    for (int idx_of_group_idx = 0; idx_of_group_idx < group_idx_size[idx_of_group]; idx_of_group_idx++)
                    {
                        (*returnColumnSizes)[*returnSize - 1]++;
                        ret[*returnSize - 1][(*returnColumnSizes)[*returnSize - 1] - 1] = (char *)malloc(sizeof(char) * (len + 1));
                        memcpy(ret[*returnSize - 1][(*returnColumnSizes)[*returnSize - 1] - 1], strs[group_idx[idx_of_group][idx_of_group_idx]], sizeof(char) * len);
                        ret[*returnSize - 1][(*returnColumnSizes)[*returnSize - 1] - 1][len] = '\0';
                    }
                }

                free(group_flag);
                free(group_char_size);
                free(group_idx);
                free(group_idx_size);
            }
        }
    }
    return ret;
}
// @lc code=end

int main(int argc, char const *argv[])
{

    char **strs = (char **)malloc(sizeof(char *) * 8);

    for (int i = 0; i < 8; i++)
    {
        strs[i] = (char *)malloc(sizeof(char));
    }
    strs[0] = "tin";
    strs[1] = "ram";
    strs[2] = "zip";
    strs[3] = "cry";
    strs[4] = "pus";
    strs[5] = "jon";
    strs[6] = "zip";
    strs[7] = "pyx";

    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));

    char ***ret = groupAnagrams(strs, 8, returnSize, returnColumnSizes);

    for (int i = 0; i < *returnSize; i++)
    {
        printf(" [ ");
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf(" %s ,", ret[i][j]);
        }
        printf(" ] \n ");
    }

    return 0;
}
