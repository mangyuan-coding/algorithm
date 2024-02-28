/*
 * @lc app=leetcode id=90 lang=c
 *
 * [90] Subsets II
 */

#include <stdio.h>

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <math.h>
#include <string.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int **subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), int_cmp);

    // define
    int ideal_size = pow(2, numsSize);
    int **subsets = (int **)malloc(sizeof(int *) * ideal_size);
    *returnColumnSizes = (int *)malloc(sizeof(int) * ideal_size);

    // init
    *returnSize = 1;
    (*returnColumnSizes)[0] = 0;
    subsets[0] = NULL;

    // loop start
    int idx = 0, same_num_size = 1, idx_of_subsets, subsets_size;
    while (idx < numsSize)
    {
        if (idx != numsSize - 1 && nums[idx] == nums[idx + 1])
        {
            same_num_size++;
        }
        else
        {
            if (same_num_size > 1)
            {
                subsets_size = *returnSize;
                for (int same_num = 1; same_num <= same_num_size; same_num++)
                {
                    idx_of_subsets = 0;
                    while (idx_of_subsets < subsets_size)
                    {
                        (*returnSize)++;
                        (*returnColumnSizes)[*returnSize - 1] = (*returnColumnSizes)[idx_of_subsets] + same_num;
                        subsets[*returnSize - 1] = (int *)malloc(sizeof(int) * (*returnColumnSizes)[*returnSize - 1]);
                        if ((*returnColumnSizes)[idx_of_subsets] > 0)
                        {
                            memcpy(subsets[*returnSize - 1], subsets[idx_of_subsets], sizeof(int) * (*returnColumnSizes)[idx_of_subsets]);
                        }
                        for (int idx_of_rest = (*returnColumnSizes)[idx_of_subsets]; idx_of_rest < (*returnColumnSizes)[*returnSize - 1]; idx_of_rest++)
                        {
                            subsets[*returnSize - 1][idx_of_rest] = nums[idx];
                        }
                        idx_of_subsets++;
                    }
                }
                same_num_size = 1;
            }
            else
            {
                idx_of_subsets = 0;
                subsets_size = *returnSize;
                while (idx_of_subsets < subsets_size)
                {
                    (*returnSize)++;
                    (*returnColumnSizes)[*returnSize - 1] = (*returnColumnSizes)[idx_of_subsets] + 1;
                    subsets[*returnSize - 1] = (int *)malloc(sizeof(int) * (*returnColumnSizes)[*returnSize - 1]);
                    if ((*returnColumnSizes)[idx_of_subsets] > 0)
                    {
                        memcpy(subsets[*returnSize - 1], subsets[idx_of_subsets], sizeof(int) * (*returnColumnSizes)[idx_of_subsets]);
                    }
                    subsets[*returnSize - 1][(*returnColumnSizes)[*returnSize - 1] - 1] = nums[idx];
                    idx_of_subsets++;
                }
            }
        }
        idx++;
    }
    return subsets;
}
// @lc code=end

int main(int argc, char const *argv[])
{
    int numsSize = 3;
    int *nums = (int *)malloc(sizeof(int) * numsSize);
    nums[0] = 1;
    nums[1] = 2;
    nums[2] = 2;
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));

    int **subsets = subsetsWithDup(nums, numsSize, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("[");
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d ", subsets[i][j]);
        }
        printf("],");
    }

    return 0;
}
