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
    pre_size = 0, cur_size = 0;

    // same num size
    int same_size = 1;

    for (int i = 0; i < candidatesSize; i++)
    {
        if (i < candidatesSize - 1 && candidates[i] == candidates[i + 1])
        {
            same_size++;
            continue;
        }

        int cur_max_size = pre_size * same_size + pre_size + same_size;
        cur = (int **)malloc(sizeof(int *) * cur_max_size);
        cur_col_size = (int *)malloc(sizeof(int) * cur_max_size);
        cur_sum = (int *)malloc(sizeof(int) * cur_max_size);

        for (int size = 1; size <= same_size; size++)
        {
            int sum = size * candidates[i];
            if (sum == target)
            {
                // add to ret
                if (*returnSize == base)
                {
                    base *= 1.5;
                    ret = (int **)realloc(ret, sizeof(int *) * base);
                    *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * base);
                }
                (*returnSize)++;
                (*returnColumnSizes)[*returnSize - 1] = size;
                ret[*returnSize - 1] = (int *)malloc(sizeof(int) * size);
                for (int k = 0; k < size; k++)
                {
                    ret[*returnSize - 1][k] = candidates[i];
                }
                break;
            }
            else if (sum < target)
            {
                cur_size++;
                cur_col_size[cur_size - 1] = size;
                cur_sum[cur_size - 1] = sum;
                cur[cur_size - 1] = (int *)malloc(sizeof(int) * size);
                for (int k = 0; k < size; k++)
                {
                    cur[cur_size - 1][k] = candidates[i];
                }
            }
            else
            {
                break;
            }
        }

        for (int j = 0; j < pre_size; j++)
        {
            cur_size++;
            cur_col_size[cur_size - 1] = pre_col_size[j];
            cur_sum[cur_size - 1] = pre_sum[j];
            cur[cur_size - 1] = (int *)malloc(sizeof(int) * pre_col_size[j]);
            memcpy(cur[cur_size - 1], pre[j], sizeof(int) * pre_col_size[j]);
        }

        for (int size = 1; size <= same_size; size++)
        {
            int sum = size * candidates[i];
            for (int j = 0; j < pre_size; j++)
            {
                if (pre_sum[j] + sum < target)
                {
                    cur_size++;
                    cur_col_size[cur_size - 1] = pre_col_size[j] + size;
                    cur_sum[cur_size - 1] = pre_sum[j] + sum;
                    cur[cur_size - 1] = (int *)malloc(sizeof(int) * cur_col_size[cur_size - 1]);
                    memcpy(cur[cur_size - 1], pre[j], sizeof(int) * pre_col_size[j]);
                    for (int k = 0; k < size; k++)
                    {
                        cur[cur_size - 1][pre_col_size[j] + k] = candidates[i];
                    }
                }
                else if (pre_sum[j] + sum == target)
                {
                    // add to result
                    if (*returnSize == base)
                    {
                        base *= 1.5;
                        ret = (int **)realloc(ret, sizeof(int *) * base);
                        *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * base);
                    }
                    (*returnSize)++;
                    (*returnColumnSizes)[*returnSize - 1] = pre_col_size[j] + size;
                    ret[*returnSize - 1] = (int *)malloc(sizeof(int) * (*returnColumnSizes)[*returnSize - 1]);
                    memcpy(ret[*returnSize - 1], pre[j], sizeof(int) * pre_col_size[j]);
                    for (int k = 0; k < size; k++)
                    {
                        ret[*returnSize - 1][pre_col_size[j] + k] = candidates[i];
                    }
                }
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

        same_size = 1;
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int candidates[] = {10, 1, 2, 7, 6, 1, 5};
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **ret = combinationSum2(candidates, 7, 8, returnSize, returnColumnSizes);
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
