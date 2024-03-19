/*
 * @lc app=leetcode.cn id=120 lang=c
 *
 * [120] Triangle
 */

// @lc code=start
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int minimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
    if (triangleSize == 0)
    {
        return 0;
    }
    else if (triangleSize == 1)
    {
        return triangle[0][0];
    }

    // f(triangleSize - 1) = min(g(triangleSize - 1, 0), g(triangleSize - 1, 1), ... , g(triangleSize - 1, triangleSize - 1))
    // g(x, y) = exit(x - 1, y) ? min(g(x - 1, y - 1), g(x - 1, y)) + (x, y) : g(x - 1, y - 1) + (x, y)
    int **path_min = (int **)malloc(sizeof(int *) * triangleSize);
    path_min[0] = (int *)malloc(sizeof(int));
    path_min[0][0] = triangle[0][0];
    for (int i = 1; i < triangleSize; i++)
    {
        path_min[i] = (int *)malloc(sizeof(int) * (i + 1));
        for (int j = 0; j <= i; j++)
        {
            if (j == 0)
            {
                path_min[i][j] = path_min[i - 1][j] + triangle[i][j];
            }
            else if (j == i)
            {
                path_min[i][j] = path_min[i - 1][j - 1] + triangle[i][j];
            }
            else
            {
                path_min[i][j] = fmin(path_min[i - 1][j], path_min[i - 1][j - 1]) + triangle[i][j];
            }
        }
    }

    int min_sum = path_min[triangleSize - 1][0];
    for (int i = 1; i < triangleSize; i++)
    {
        if (path_min[triangleSize - 1][i] < min_sum)
        {
            min_sum = path_min[triangleSize - 1][i];
        }
    }

    return min_sum;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int **triangle = (int **)malloc(sizeof(int *) * 4);
    triangle[0] = (int *)malloc(sizeof(int));
    triangle[0][0] = 2;
    triangle[1] = (int *)malloc(sizeof(int) * 2);
    triangle[1][0] = 3;
    triangle[1][1] = 4;
    triangle[2] = (int *)malloc(sizeof(int) * 3);
    triangle[2][0] = 6;
    triangle[2][1] = 5;
    triangle[2][2] = 7;
    triangle[3] = (int *)malloc(sizeof(int) * 4);
    triangle[3][0] = 4;
    triangle[3][1] = 1;
    triangle[3][2] = 8;
    triangle[3][3] = 3;
    int triangleSize = 4;
    int *triangleColSize = (int *)malloc(sizeof(int) * 4);
    triangleColSize[0] = 1;
    triangleColSize[1] = 2;
    triangleColSize[2] = 3;
    triangleColSize[3] = 4;
    int minimum = minimumTotal(triangle, triangleSize, triangleColSize);
    return 0;
}
