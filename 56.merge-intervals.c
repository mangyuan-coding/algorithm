/*
 * @lc app=leetcode id=56 lang=c
 *
 * [56] Merge Intervals
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdlib.h>

int double_int_cmp(const void *a, const void *b)
{
    int **arg_a = (int **)a;
    int **arg_b = (int **)b;
    int arg_a_0 = arg_a[0][0];
    int arg_a_1 = arg_a[0][1];
    int arg_b_0 = arg_b[0][0];
    int arg_b_1 = arg_b[0][1];
    return (arg_a_0 == arg_b_0 ? arg_a_1 - arg_b_1 : arg_a_0 - arg_b_0);
}

int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes)
{
    if (intervalsSize == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    if (intervalsSize == 1)
    {
        *returnSize = 1;
        *returnColumnSizes = (int *)malloc(sizeof(int));
        (*returnColumnSizes)[0] = 2;
        return intervals;
    }

    qsort(intervals, intervalsSize, sizeof(int *), double_int_cmp);

    int **ret = (int **)malloc(sizeof(int *) * intervalsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * intervalsSize);

    *returnSize = 1;
    (*returnColumnSizes)[0] = 2;
    ret[0] = (int *)malloc(sizeof(int) * 2);
    ret[0][0] = intervals[0][0];
    ret[0][1] = intervals[0][1];

    for (int i = 1; i < intervalsSize; i++)
    {
        if (intervals[i][0] <= ret[*returnSize - 1][1])
        {
            if (intervals[i][1] > ret[*returnSize - 1][1])
            {
                ret[*returnSize - 1][1] = intervals[i][1];
            }
        }
        else
        {
            (*returnSize)++;
            (*returnColumnSizes)[*returnSize - 1] = 2;
            ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
            ret[*returnSize - 1][0] = intervals[i][0];
            ret[*returnSize - 1][1] = intervals[i][1];
        }
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int **intervals = (int **)malloc(sizeof(int *) * 4);
    int *intervalsColSize = (int *)malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++)
    {
        intervals[i] = (int *)malloc(sizeof(int) * 2);
        intervalsColSize[i] = 2;
    }

    intervals[0][0] = 1;
    intervals[0][1] = 3;
    intervals[1][0] = 2;
    intervals[1][1] = 6;
    intervals[2][0] = 8;
    intervals[2][1] = 10;
    intervals[3][0] = 15;
    intervals[3][1] = 18;

    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **ret = merge(intervals, 4, intervalsColSize, returnSize, returnColumnSizes);

    for (int i = 0; i < *returnSize; i++)
    {
        printf("%d [", i);
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d ", ret[i][j]);
        }

        printf("]\n", i);
    }

    return 0;
}
