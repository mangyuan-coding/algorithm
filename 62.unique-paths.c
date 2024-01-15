/*
 * @lc app=leetcode id=62 lang=c
 *
 * [62] Unique Paths
 */

// @lc code=start
#include <stdlib.h>

int uniquePaths(int m, int n)
{
    int **paths = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        paths[i] = (int *)malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
            {
                paths[i][j] = 1;
            }
            else if (i == 0)
            {
                paths[i][j] = paths[i][j - 1];
            }
            else if (j == 0)
            {
                paths[i][j] = paths[i - 1][j];
            }
            else
            {
                paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
            }
        }
    }
    return paths[n - 1][m - 1];
}
// @lc code=end