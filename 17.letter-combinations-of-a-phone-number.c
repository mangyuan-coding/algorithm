/*
 * @lc app=leetcode id=17 lang=c
 *
 * [17] Letter Combinations of a Phone Number
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char *dig_char[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
char **letterCombinations(char *digits, int *returnSize)
{

    int len = strlen(digits);
    if (len == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    char **matrix = (char **)malloc(sizeof(char *) * len);
    int *matrix_row_len = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
    {
        char *sub_char = (char *)dig_char[digits[i] - '0'];
        int row_len = strlen(sub_char);
        matrix_row_len[i] = row_len;
        matrix[i] = (char *)malloc(sizeof(char) * (row_len + 1));
        matrix[i][row_len] = '\0';
        strcpy(matrix[i], sub_char);
    }
    int *trace = (int *)malloc(sizeof(int) * len);
    trace[0] = 0;
    char **ret = (char **)malloc(sizeof(char *) * pow(4, len));
    *returnSize = 0;
    ret[*returnSize] = (char *)malloc(sizeof(char) * (len + 1));
    ret[*returnSize][len] = '\0';
    int level = 0;
    while (1)
    {
        ret[*returnSize][level] = matrix[level][trace[level]];
        if (level == len - 1)
        {
            (*returnSize)++;
            while (level >= 0)
            {
                if (level == 0 && trace[level] == matrix_row_len[level] - 1)
                {
                    return ret;
                }
                if (trace[level] < matrix_row_len[level] - 1)
                {
                    trace[level]++;
                    break;
                }
                else
                {
                    level--;
                }
            }
            ret[*returnSize] = (char *)malloc(sizeof(char) * (len + 1));
            ret[*returnSize][len] = '\0';
            if (*returnSize > 0)
            {
                strcpy(ret[*returnSize], ret[*returnSize - 1]);
            }
        }
        else
        {
            level++;
            trace[level] = 0;
        }
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char digits[] = "7";
    int *returnSize = malloc(sizeof(int));
    char **ret = letterCombinations(digits, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%d is %s\n", i, ret[i]);
    }
    return 0;
}
