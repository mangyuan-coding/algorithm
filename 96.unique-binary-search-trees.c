/*
 * @lc app=leetcode.cn id=96 lang=c
 *
 * [96] Unique Binary Search Trees
 */

// @lc code=start
#include <stdlib.h>

int numTrees(int n)
{
    int **sub_tree_size = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        sub_tree_size[i] = (int *)malloc(sizeof(int) * n);
    }

    for (int distence = 0, ideal_size; distence < n; distence++)
    {
        for (int i = 0, j; i < n - distence; i++)
        {
            if (distence == 0)
            {
                ideal_size = 1;
                sub_tree_size[i][i] = ideal_size;
            }
            else
            {
                j = i + distence;
                ideal_size = 0;
                for (int root = i; root <= j; root++)
                {
                    if (i > root - 1)
                    {
                        ideal_size += sub_tree_size[root + 1][j];
                    }
                    else if (root + 1 > j)
                    {
                        ideal_size += sub_tree_size[i][root - 1];
                    }
                    else
                    {
                        ideal_size += sub_tree_size[i][root - 1] * sub_tree_size[root + 1][j];
                    }
                }
                sub_tree_size[i][j] = ideal_size;
            }
        }
    }
    return sub_tree_size[0][n - 1];
}
// @lc code=end
