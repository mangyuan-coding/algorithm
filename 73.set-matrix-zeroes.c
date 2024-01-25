/*
 * @lc app=leetcode id=73 lang=c
 *
 * [73] Set Matrix Zeroes
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

void setZeroes(int **matrix, int matrixSize, int *matrixColSize)
{
    if (matrixSize <= matrixColSize[0])
    {
        bool *zero_m = (bool *)malloc(sizeof(bool) * matrixSize);
        for (int i = 0; i < matrixSize; i++)
        {
            zero_m[i] = false;
        }
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixColSize[i]; j++)
            {
                if (matrix[i][j] == 0)
                {
                    zero_m[i] = true;
                }
            }
        }

        for (int j = 0; j < matrixColSize[0]; j++)
        {
            bool has_zero = false;
            for (int i = 0; i < matrixSize; i++)
            {
                if (matrix[i][j] == 0)
                {
                    has_zero = true;
                }
            }
            if (has_zero)
            {
                for (int i = 0; i < matrixSize; i++)
                {
                    matrix[i][j] = 0;
                }
            }
            else
            {
                for (int i = 0; i < matrixSize; i++)
                {
                    if (zero_m[i])
                    {
                        matrix[i][j] = 0;
                    }
                }
            }
        }
    }
    else
    {
        bool *zero_n = (bool *)malloc(sizeof(bool) * matrixColSize[0]);
        for (int i = 0; i < matrixColSize[0]; i++)
        {
            zero_n[i] = false;
        }
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixColSize[i]; j++)
            {
                if (matrix[i][j] == 0)
                {
                    zero_n[j] = true;
                }
            }
        }

        for (int i = 0; i < matrixSize; i++)
        {
            bool has_zero = false;
            for (int j = 0; j < matrixColSize[i]; j++)
            {
                if (matrix[i][j] == 0)
                {
                    has_zero = true;
                }
            }
            if (has_zero)
            {
                for (int j = 0; j < matrixColSize[i]; j++)
                {
                    matrix[i][j] = 0;
                }
            }
            else
            {
                for (int j = 0; j < matrixColSize[i]; j++)
                {
                    if (zero_n[j])
                    {
                        matrix[i][j] = 0;
                    }
                }
            }
        }
    }
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int **matrix = (int **)malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * 3);
    }
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[2][0] = 1;
    matrix[2][1] = 1;
    matrix[2][2] = 1;

    int *matrixColSize = (int *)malloc(sizeof(int) * 3);
    matrixColSize[0] = 3;
    matrixColSize[1] = 3;
    matrixColSize[2] = 3;

    setZeroes(matrix, 3, matrixColSize);
    return 0;
}
