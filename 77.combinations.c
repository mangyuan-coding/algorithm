/*
 * @lc app=leetcode id=77 lang=c
 *
 * [77] Combinations
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

int **combine(int n, int k, int *returnSize, int **returnColumnSizes)
{
    int ***pre_combines = NULL, *pre_size = NULL;
    pre_size = (int *)malloc(sizeof(int));
    pre_size[0] = 1;
    pre_combines = (int ***)malloc(sizeof(int **));
    pre_combines[0] = (int **)malloc(sizeof(int *));
    pre_combines[0][0] = (int *)malloc(sizeof(int));
    pre_combines[0][0][0] = 1;

    int ***cur_combines = NULL, *cur_size = NULL;
    for (int i = 2; i <= n; i++)
    {
        cur_size = (int *)malloc(sizeof(int) * k);
        cur_combines = (int ***)malloc(sizeof(int **) * k);
        for (int j = 1; j <= k; j++)
        {
            if (j > i)
            {
                break;
            }
            int ideal_size = (i - 1 < j ? 0 : pre_size[j - 1]) + (j == 1 ? 1 : pre_size[j - 2]);
            cur_size[j - 1] = 0;
            cur_combines[j - 1] = (int **)malloc(sizeof(int *) * ideal_size);
            if (j <= i - 1)
            {
                for (int pre_idx = 0; pre_idx < pre_size[j - 1]; pre_idx++)
                {
                    cur_size[j - 1]++;
                    cur_combines[j - 1][cur_size[j - 1] - 1] = (int *)malloc(sizeof(int) * j);
                    memcpy(cur_combines[j - 1][cur_size[j - 1] - 1], pre_combines[j - 1][pre_idx], sizeof(int) * j);
                }
            }
            if (j != 1)
            {
                for (int pre_idx = 0; pre_idx < pre_size[j - 2]; pre_idx++)
                {
                    cur_size[j - 1]++;
                    cur_combines[j - 1][cur_size[j - 1] - 1] = (int *)malloc(sizeof(int) * j);
                    memcpy(cur_combines[j - 1][cur_size[j - 1] - 1], pre_combines[j - 2][pre_idx], sizeof(int) * (j - 1));
                    cur_combines[j - 1][cur_size[j - 1] - 1][j - 1] = i;
                }
            }
            else
            {
                cur_size[j - 1]++;
                cur_combines[j - 1][cur_size[j - 1] - 1] = (int *)malloc(sizeof(int));
                cur_combines[j - 1][cur_size[j - 1] - 1][j - 1] = i;
            }
        }
        free(pre_size);
        free(pre_combines);
        pre_combines = cur_combines;
        pre_size = cur_size;
    }
    *returnSize = pre_size[k - 1];
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = k;
    }

    free(pre_size);
    return pre_combines[k - 1];
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));

    int **ret = combine(4, 2, returnSize, returnColumnSizes);

    for (int i = 0; i < *returnSize; i++)
    {
        printf("[ ");
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d ", ret[i][j]);
        }
        printf("] \n");
    }

    return 0;
}
