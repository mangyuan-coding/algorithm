/*
 * @lc app=leetcode id=118 lang=c
 *
 * [118] Pascal's Triangle
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int **generate(int numRows, int *returnSize, int **returnColumnSizes)
{
    int **ret = (int **)malloc(sizeof(int *) * numRows);
    *returnColumnSizes = (int *)malloc(sizeof(int) * numRows);
    *returnSize = 0;

    // init 1
    *returnSize = 1;
    (*returnColumnSizes)[0] = 1;
    ret[0] = (int *)malloc(sizeof(int));
    ret[0][0] = 1;
    if (numRows == 1)
    {
        return ret;
    }

    for (int row = 2; row <= numRows; row++)
    {
        (*returnSize)++;
        (*returnColumnSizes)[row - 1] = row;
        ret[row - 1] = (int *)malloc(sizeof(int) * row);

        for (int idx = 0; idx < row; idx++)
        {
            if (idx == 0)
            {
                ret[row - 1][idx] = ret[row - 2][idx];
            }
            else if (idx == row - 1)
            {
                ret[row - 1][idx] = ret[row - 2][idx - 1];
            }
            else
            {
                ret[row - 1][idx] = ret[row - 2][idx - 1] + ret[row - 2][idx];
            }
        }
    }

    return ret;
}
// @lc code=end
