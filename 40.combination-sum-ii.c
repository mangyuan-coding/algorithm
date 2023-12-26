/*
 * @lc app=leetcode id=40 lang=c
 *
 * [40] Combination Sum II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void *a, const void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}

int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
    if (candidatesSize <= 0)
    {
        *returnSize = 0;
        return NULL;
    }
    qsort(candidates, candidatesSize, sizeof(int), compare);
    if (candidates[0] > target)
    {
        *returnSize = 0;
        return NULL;
    }

    // define result
    int base;
    int **ret;
    // init result
    base = 100;
    *returnSize = 0;
    *returnColumnSizes = malloc(sizeof(int) * base);
    ret = (int **)malloc(sizeof(int *) * base);

    // define pre
    int **pre = (int **)malloc(sizeof(int *)), **cur;
    int pre_size, cur_size;
    int *pre_sum = (int *)malloc(sizeof(int)), *cur_sum;
    int *pre_col_size = (int *)malloc(sizeof(int)), *cur_col_size;
    // init pre
    pre_size = 1;
    pre[0] = (int *)malloc(sizeof(int));
    pre[0][0] = candidates[0];
    pre_sum[0] = candidates[0];
    pre_col_size[0] = 1;

    int same_size = 1;

    for (int i = 0; i < candidatesSize; i++)
    {
        int num = candidates[i];

        if (num == candidates[i + 1] && i < candidatesSize - 1)
        {
            same_size++;
            continue;
        }

        if (num == target)
        {
            // add to ret
            if (*returnSize == base)
            {
                base *= 1.5;
                ret = (int **)realloc(ret, sizeof(int *) * base);
                *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * base);
            }
            (*returnSize)++;
            (*returnColumnSizes)[*returnSize - 1] = 1;
            ret[*returnSize - 1] = (int *)malloc(sizeof(int));
            ret[*returnSize - 1][0] = num;
            break;
        }
        if (num > target)
        {
            break;
        }

        cur = (int **)malloc(sizeof(int *) * (pre_size * 2 + 1));
        cur_col_size = (int *)malloc(sizeof(int) * (pre_size * 2 + 1));
        cur_sum = (int *)malloc(sizeof(int) * (pre_size * 2 + 1));

        if (candidates[i] != candidates[i - 1])
        {
            cur_size = 1;
            cur_col_size[cur_size - 1] = 1;
            cur_sum[cur_size - 1] = num;
            cur[cur_size - 1] = (int *)malloc(sizeof(int));
            cur[cur_size - 1][0] = num;
        }
        else
        {
            cur_size = 0;
        }

        for (int j = 0; j < pre_size; j++)
        {
            cur_size++;
            cur_col_size[cur_size - 1] = pre_col_size[j];
            cur_sum[cur_size - 1] = pre_sum[j];
            cur[cur_size - 1] = (int *)malloc(sizeof(int) * pre_col_size[j]);
            memcpy(cur[cur_size - 1], pre[j], sizeof(int) * pre_col_size[j]);

            if (pre_sum[j] + num < target)
            {
                cur_size++;
                cur_col_size[cur_size - 1] = pre_col_size[j] + 1;
                cur_sum[cur_size - 1] = pre_sum[j] + num;
                cur[cur_size - 1] = (int *)malloc(sizeof(int) * (pre_col_size[j] + 1));
                memcpy(cur[cur_size - 1], pre[j], sizeof(int) * pre_col_size[j]);
                cur[cur_size - 1][cur_col_size[cur_size - 1] - 1] = num;
            }
            else if (pre_sum[j] + num == target)
            {
                // add to result
                if (*returnSize == base)
                {
                    base *= 1.5;
                    ret = (int **)realloc(ret, sizeof(int *) * base);
                    *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * base);
                }
                (*returnSize)++;
                (*returnColumnSizes)[*returnSize - 1] = pre_col_size[j] + 1;
                ret[*returnSize - 1] = (int *)malloc(sizeof(int) * (*returnColumnSizes)[*returnSize - 1]);
                memcpy(ret[*returnSize - 1], pre[j], sizeof(int) * pre_col_size[j]);
                ret[*returnSize - 1][(*returnColumnSizes)[*returnSize - 1] - 1] = num;
            }
        }

        free(pre);
        free(pre_sum);
        free(pre_col_size);

        pre_size = cur_size;
        pre = cur;
        pre_sum = cur_sum;
        pre_col_size = cur_col_size;

        cur_size = 0;
        cur = NULL;
        cur_sum = NULL;
        cur_col_size = NULL;
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int candidates[] = {4, 4, 2, 1, 4, 2, 2, 1, 3};
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **ret = combinationSum2(candidates, 9, 6, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("i[%d] is [", i);
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d, ", ret[i][j]);
        }
        printf("]. \n");
    }

    return 0;
}
