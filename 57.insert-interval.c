/*
 * @lc app=leetcode id=57 lang=c
 *
 * [57] Insert Interval
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int **insert(int **intervals, int intervalsSize, int *intervalsColSize, int *newInterval, int newIntervalSize, int *returnSize, int **returnColumnSizes)
{
    if (intervalsSize == 0 && newIntervalSize == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    if (intervalsSize == 0)
    {
        *returnSize = 1;
        int **ret = (int **)malloc(sizeof(int *));
        *returnColumnSizes = (int *)malloc(sizeof(int));
        (*returnColumnSizes)[0] = 2;
        ret[0] = (int *)malloc(sizeof(int) * 2);
        ret[0][0] = newInterval[0];
        ret[0][1] = newInterval[1];
        return ret;
    }
    if (newIntervalSize == 0)
    {
        *returnSize = intervalsSize;
        *returnColumnSizes = (int *)malloc(sizeof(int) * intervalsSize);
        for (int i = 0; i < intervalsSize; i++)
        {
            (*returnColumnSizes)[i] = 2;
        }
        return intervals;
    }

    int **ret = (int **)malloc(sizeof(int *) * (intervalsSize + newIntervalSize));
    *returnColumnSizes = (int *)malloc(sizeof(int) * (intervalsSize + newIntervalSize));
    *returnSize = 0;

    // find first
    if (intervals[0][0] > newInterval[1])
    {
        *returnSize = 1;
        (*returnColumnSizes)[*returnSize - 1] = 2;
        ret[0] = (int *)malloc(sizeof(int) * 2);
        ret[0][0] = newInterval[0];
        ret[0][1] = newInterval[1];

        for (int i = 0; i < intervalsSize; i++)
        {
            (*returnSize)++;
            (*returnColumnSizes)[*returnSize - 1] = 2;
            ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
            ret[*returnSize - 1][0] = intervals[i][0];
            ret[*returnSize - 1][1] = intervals[i][1];
        }

        return ret;
    }

    // find first
    if (intervals[intervalsSize - 1][1] < newInterval[0])
    {

        for (int i = 0; i < intervalsSize; i++)
        {
            (*returnSize)++;
            (*returnColumnSizes)[*returnSize - 1] = 2;
            ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
            ret[*returnSize - 1][0] = intervals[i][0];
            ret[*returnSize - 1][1] = intervals[i][1];
        }

        (*returnSize)++;
        (*returnColumnSizes)[*returnSize - 1] = 2;
        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
        ret[*returnSize - 1][0] = newInterval[0];
        ret[*returnSize - 1][1] = newInterval[1];

        return ret;
    }

    int idx_of_intervals = 0;
    // find start
    while (1)
    {
        if (intervals[idx_of_intervals][1] < newInterval[0])
        {
            (*returnSize)++;
            (*returnColumnSizes)[*returnSize - 1] = 2;
            ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
            ret[*returnSize - 1][0] = intervals[idx_of_intervals][0];
            ret[*returnSize - 1][1] = intervals[idx_of_intervals][1];
            idx_of_intervals++;
        }
        else
        {
            break;
        }
    }

    int start = intervals[idx_of_intervals][0] < newInterval[0] ? intervals[idx_of_intervals][0] : newInterval[0];

    // find end
    while (idx_of_intervals < intervalsSize)
    {
        if (intervals[idx_of_intervals][1] > newInterval[1])
        {
            break;
        }

        idx_of_intervals++;
    }

    if (idx_of_intervals == intervalsSize)
    {
        (*returnSize)++;
        (*returnColumnSizes)[*returnSize - 1] = 2;
        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
        ret[*returnSize - 1][0] = start;
        ret[*returnSize - 1][1] = newInterval[1];
        return ret;
    }

    if (intervals[idx_of_intervals][0] > newInterval[1])
    {
        (*returnSize)++;
        (*returnColumnSizes)[*returnSize - 1] = 2;
        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
        ret[*returnSize - 1][0] = start;
        ret[*returnSize - 1][1] = newInterval[1];
    }
    else
    {
        (*returnSize)++;
        (*returnColumnSizes)[*returnSize - 1] = 2;
        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
        ret[*returnSize - 1][0] = start;
        ret[*returnSize - 1][1] = intervals[idx_of_intervals][1];
        idx_of_intervals++;
    }

    for (; idx_of_intervals < intervalsSize; idx_of_intervals++)
    {
        (*returnSize)++;
        (*returnColumnSizes)[*returnSize - 1] = 2;
        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * 2);
        ret[*returnSize - 1][0] = intervals[idx_of_intervals][0];
        ret[*returnSize - 1][1] = intervals[idx_of_intervals][1];
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int **intervals = (int **)malloc(sizeof(int *));
    intervals[0] = (int *)malloc(sizeof(int) * 2);
    intervals[0][0] = 1;
    intervals[0][1] = 5;
    int *intervalsColSize = (int *)malloc(sizeof(int));
    intervalsColSize[0] = 2;
    int *newInterval = (int *)malloc(sizeof(int) * 2);
    newInterval[0] = 2;
    newInterval[1] = 7;
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **ret = insert(intervals, 1, intervalsColSize, newInterval, 2, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf(" %d, %d \n", ret[i][0], ret[i][1]);
    }

    return 0;
}
