/*
 * @lc app=leetcode id=74 lang=c
 *
 * [74] Search a 2D Matrix
 */

#include <stdbool.h>

// @lc code=start
bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{

    if (matrix[0][0] == target || matrix[matrixSize - 1][matrixColSize[0] - 1] == target)
    {
        return true;
    }

    int left = 0, right = matrixSize * matrixColSize[0] - 1, n = matrixColSize[0], half, half_value;
    while (left < right)
    {
        half = (left + right) / 2;
        if (half == left)
        {
            return false;
        }
        half_value = matrix[half / n][half % n];
        if (half_value == target)
        {
            return true;
        }
        else if (half_value < target)
        {
            left = half;
        }
        else
        {
            right = half;
        }
    }

    return false;
}
// @lc code=end
