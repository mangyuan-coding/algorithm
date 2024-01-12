/*
 * @lc app=leetcode id=54 lang=c
 *
 * [54] Spiral Matrix
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
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

int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize)
{
    int max_size = matrixSize * matrixColSize[0];
    int *ret = (int *)malloc(sizeof(int) * max_size);
    *returnSize = 0;

    int rectangle_times = 0;

    int cur_rect_m = matrixSize;
    int cur_rect_n = matrixColSize[0];
    bool cur_rect_finished = false;

    int trace_x = 0, trace_y = 0;

    enum direction dire = R;

    while (*returnSize <= max_size)
    {
        // idx_x = rectangle - 1 + trace_x;
        // idx_y = rectangle - 1 + trace_y;
        (*returnSize)++;
        ret[*returnSize - 1] = matrix[rectangle_times + trace_x][rectangle_times + trace_y];

        // next step
        switch (dire)
        {
        case R:
            if (trace_y < cur_rect_n - 1)
            {
                trace_y++;
            }
            else
            {
                // trace_y == cur_rect_n - 1, turn D
                dire = D;
                trace_x++;
                if (trace_x == cur_rect_m)
                {
                    // no route
                    cur_rect_finished = true;
                    break;
                }
            }
            break;
        case D:
            if (trace_x < cur_rect_m - 1)
            {
                trace_x++;
            }
            else
            {
                dire = L;
                trace_y--;
                if (trace_y < 0)
                {
                    cur_rect_finished = true;
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
                    cur_rect_finished = true;
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
                cur_rect_finished = true;
            }
            break;
        default:
            break;
        }

        if (cur_rect_finished)
        {
            // trace_x == 1 means finish cur rectangle;
            // into inner rectangle
            rectangle_times++;
            cur_rect_m -= 2;
            cur_rect_n -= 2;
            cur_rect_finished = false;

            // reset
            trace_x = 0;
            trace_y = 0;
            dire = R;
        }
        // no rectangle
        if (cur_rect_m < 1 || cur_rect_n < 1)
        {
            break;
        }
    }

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int **matrix = (int **)malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * 2);
    }

    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;

    int *matrixColSize = (int *)malloc(sizeof(int) * 2);
    matrixColSize[0] = 2;
    matrixColSize[1] = 2;

    int *returnSize = (int *)malloc(sizeof(int));

    int *ret = spiralOrder(matrix, 2, matrixColSize, returnSize);

    for (int i = 0; i < *returnSize; i++)
    {
        printf("%d ", ret[i]);
    }

    return 0;
}
