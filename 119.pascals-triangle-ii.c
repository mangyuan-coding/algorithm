/*
 * @lc app=leetcode id=119 lang=c
 *
 * [119] Pascal's Triangle II
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int *getRow(int rowIndex, int *returnSize)
{
    int *row_nums = (int *)malloc(sizeof(int) * (rowIndex + 1));
    *returnSize = rowIndex + 1;

    row_nums[0] = 1;

    for (int row_idx = 1; row_idx <= rowIndex; row_idx++)
    {
        for (int idx_per_row = row_idx; idx_per_row >= 0; idx_per_row--)
        {
            if (idx_per_row == row_idx)
            {
                row_nums[idx_per_row] = row_nums[idx_per_row - 1];
            }
            else if (idx_per_row == 0)
            {
                row_nums[idx_per_row] = row_nums[idx_per_row];
            }
            else
            {
                row_nums[idx_per_row] = row_nums[idx_per_row] + row_nums[idx_per_row - 1];
            }
        }
    }

    return row_nums;
}
// @lc code=end
