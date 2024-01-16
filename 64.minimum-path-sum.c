/*
 * @lc app=leetcode id=64 lang=c
 *
 * [64] Minimum Path Sum
 */

// @lc code=start
#include <math.h>

int minPathSum(int **grid, int gridSize, int *gridColSize)
{
    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridColSize[row]; col++)
        {
            if (row == 0 && col == 0)
            {
                continue;
            }
            if (row == 0)
            {
                grid[row][col] += grid[row][col - 1];
            }
            else if (col == 0)
            {
                grid[row][col] += grid[row - 1][col];
            }
            else
            {
                grid[row][col] += fmin(grid[row - 1][col], grid[row][col - 1]);
            }
        }
    }
    return grid[gridSize - 1][gridColSize[gridSize - 1] - 1];
}
// @lc code=end
