/*
 * @lc app=leetcode id=63 lang=c
 *
 * [63] Unique Paths II
 */

// @lc code=start
int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize, int *obstacleGridColSize)
{

    for (int y = 0; y < obstacleGridSize; y++)
    {
        for (int x = 0; x < obstacleGridColSize[y]; x++)
        {
            if (obstacleGrid[y][x] == 1)
            {
                obstacleGrid[y][x] = 0;
                continue;
            }

            if (x == 0 && y == 0)
            {
                obstacleGrid[y][x] = 1;
            }
            else if (y == 0)
            {
                obstacleGrid[y][x] = obstacleGrid[y][x - 1];
            }
            else if (x == 0)
            {
                obstacleGrid[y][x] = obstacleGrid[y - 1][x];
            }
            else
            {
                if (obstacleGrid[y - 1][x] == 0 && obstacleGrid[y][x - 1] == 0)
                {
                    obstacleGrid[y][x] = 0;
                }
                else if (obstacleGrid[y - 1][x] == 0)
                {
                    obstacleGrid[y][x] = obstacleGrid[y][x - 1];
                }
                else if (obstacleGrid[y][x - 1] == 0)
                {
                    obstacleGrid[y][x] = obstacleGrid[y - 1][x];
                }
                else
                {
                    obstacleGrid[y][x] = obstacleGrid[y - 1][x] + obstacleGrid[y][x - 1];
                }
            }
        }
    }

    return obstacleGrid[obstacleGridSize - 1][obstacleGridColSize[obstacleGridSize - 1] - 1];
}
// @lc code=end
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int obstacleGridSize = 3;

    int *obstacleGridColSize = (int *)malloc(sizeof(int) * 3);
    obstacleGridColSize[0] = 3;
    obstacleGridColSize[1] = 3;
    obstacleGridColSize[2] = 3;

    int **obstacleGrid = (int **)malloc(sizeof(int *) * 3);
    obstacleGrid[0] = (int *)malloc(sizeof(int) * 3);
    obstacleGrid[1] = (int *)malloc(sizeof(int) * 3);
    obstacleGrid[2] = (int *)malloc(sizeof(int) * 3);
    obstacleGrid[0][0] = 0;
    obstacleGrid[0][1] = 0;
    obstacleGrid[0][2] = 0;
    obstacleGrid[1][0] = 0;
    obstacleGrid[1][1] = 1;
    obstacleGrid[1][2] = 0;
    obstacleGrid[2][0] = 0;
    obstacleGrid[2][1] = 0;
    obstacleGrid[2][2] = 0;

    printf("%d", uniquePathsWithObstacles(obstacleGrid, 3, obstacleGridColSize));
    return 0;
}
