/*
 * @lc app=leetcode id=59 lang=c
 *
 * [59] Spiral Matrix II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

enum direction
{
    // RIGHT
    R,
    // DOWN
    D,
    // LEFT
    L,
    // UP
    U
};

int **generateMatrix(int n, int *returnSize, int **returnColumnSizes)
{
    if (n == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    if (n == 1)
    {
        *returnSize = 1;
        *returnColumnSizes = (int *)malloc(sizeof(int));
        (*returnColumnSizes)[0] = 1;
        int **matrix = (int **)malloc(sizeof(int *));
        matrix[0] = (int *)malloc(sizeof(int));
        matrix[0][0] = 1;
        return matrix;
    }

    int **matrix = (int **)malloc(sizeof(int *) * n);
    *returnColumnSizes = (int *)malloc(sizeof(int) * n);
    *returnSize = n;
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * n);
        (*returnColumnSizes)[i] = n;
    }

    int square_times = 0;

    int cur_square_len = n;
    bool cur_square_finished = false;

    int trace_x = 0, trace_y = 0;
    int cur_num = 1;

    enum direction dire = R;

    while (1)
    {
        // idx_x = square_times + trace_x;
        // idx_y = square_times + trace_y;
        matrix[square_times + trace_x][square_times + trace_y] = cur_num++;

        // next step
        switch (dire)
        {
        case R:
            if (trace_y < cur_square_len - 1)
            {
                trace_y++;
            }
            else
            {
                // trace_y == cur_rect_n - 1, turn D
                dire = D;
                trace_x++;
                if (trace_x == cur_square_len)
                {
                    // no route
                    cur_square_finished = true;
                    break;
                }
            }
            break;
        case D:
            if (trace_x < cur_square_len - 1)
            {
                trace_x++;
            }
            else
            {
                dire = L;
                trace_y--;
                if (trace_y < 0)
                {
                    cur_square_finished = true;
                    break;
                }
            }
            break;
        case L:
            if (trace_y > 0)
            {
                trace_y--;
            }
            else
            {
                dire = U;
                trace_x--;
                if (trace_x < 1)
                {
                    cur_square_finished = true;
                }
            }
            break;
        case U:
            if (trace_x > 1)
            {
                trace_x--;
            }
            else
            {
                cur_square_finished = true;
            }
            break;
        default:
            break;
        }

        if (cur_square_finished)
        {
            // trace_x == 1 means finish cur rectangle;
            // into inner rectangle
            square_times++;
            cur_square_len -= 2;
            cur_square_finished = false;

            // reset
            trace_x = 0;
            trace_y = 0;
            dire = R;
        }
        // no rectangle
        if (cur_square_len < 1)
        {
            break;
        }
    }
    return matrix;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n = 1;
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **matrix = generateMatrix(n, returnSize, returnColumnSizes);

    for (int i = 0; i < *returnSize; i++)
    {
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf(" %d, ", matrix[i][j]);
        }
    }

    return 0;
}
