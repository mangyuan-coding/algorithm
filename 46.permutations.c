/*
 * @lc app=leetcode id=46 lang=c
 *
 * [46] Permutations
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    if (numsSize == 0)
    {
        return NULL;
    }
    int **ret = (int **)malloc(sizeof(int *));
    *returnColumnSizes = (int *)malloc(sizeof(int));
    *returnSize = 1;
    (*returnColumnSizes)[0] = 1;
    ret[0] = (int *)malloc(sizeof(int));
    ret[0][0] = nums[0];
    if (numsSize == 1)
    {
        return ret;
    }

    int **pre = ret;
    int pre_column_sizes = (*returnColumnSizes)[0];
    int pre_size = *returnSize;
    for (int i = 1; i < numsSize; i++)
    {
        ret = (int **)malloc(sizeof(int *) * (pre_size * (pre_column_sizes + 1)));
        *returnSize = 0;

        int num = nums[i];
        for (int j = 0; j < pre_size; j++)
        {
            for (int k = 0; k <= pre_column_sizes; k++)
            {
                (*returnSize)++;
                ret[*returnSize - 1] = (int *)malloc(sizeof(int) * (pre_column_sizes + 1));
                ret[*returnSize - 1][k] = num;
                if (k == 0)
                {
                    memcpy(ret[*returnSize - 1] + 1, pre[j], sizeof(int) * pre_column_sizes);
                }
                else if (k == pre_column_sizes)
                {
                    memcpy(ret[*returnSize - 1], pre[j], sizeof(int) * pre_column_sizes);
                }
                else
                {
                    memcpy(ret[*returnSize - 1], pre[j], sizeof(int) * k);
                    memcpy(ret[*returnSize - 1] + k + 1, pre[j] + k, sizeof(int) * (pre_column_sizes - k));
                }
            }
        }
        free(pre);
        pre = ret;
        pre_size = *returnSize;
        pre_column_sizes++;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[3] = {1, 2, 3};
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **ret = permute(nums, 3, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("i is %d, [", i);
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d,", ret[i][j]);
        }
        printf("] \n");
    }

    return 0;
}
