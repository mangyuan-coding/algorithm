/*
 * @lc app=leetcode id=18 lang=c
 *
 * [18] 4Sum
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes)
{
    int base = 100;
    int **ret = (int **)malloc(sizeof(int *) * base);
    *returnColumnSizes = (int *)malloc(sizeof(int) * base);
    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), int_cmp);

    for (int i = 0; i < numsSize; i++)
    {
        if (i != 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        for (int j = i + 1; j < numsSize; j++)
        {
            if (j != i + 1 && nums[j] == nums[j - 1])
            {
                continue;
            }
            int left = j + 1, right = numsSize - 1;
            while (left < right)
            {
                long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target)
                {
                    if (*returnSize == base)
                    {
                        base *= 1.5;
                        ret = (int **)malloc(sizeof(int *) * base);
                        *returnColumnSizes = (int *)malloc(sizeof(int) * base);
                    }
                    ret[*returnSize] = (int *)malloc(sizeof(int) * 4);
                    ret[*returnSize][0] = nums[i];
                    ret[*returnSize][1] = nums[j];
                    ret[*returnSize][2] = nums[left];
                    ret[*returnSize][3] = nums[right];
                    (*returnColumnSizes)[*returnSize] = 4;
                    (*returnSize)++;
                    while (left < right)
                    {
                        left++;
                        if (nums[left] != nums[left - 1])
                        {
                            break;
                        }
                    }
                }
                else if (sum < target)
                {
                    while (left < right)
                    {
                        left++;
                        if (nums[left] != nums[left - 1])
                        {
                            break;
                        }
                    }
                }
                else
                {
                    while (left < right)
                    {
                        right--;
                        if (nums[right] != nums[right + 1])
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {1000000000, 1000000000, 1000000000, 1000000000};
    int base = 108;
    int *returnSize = (int *)malloc(sizeof(int) * base);
    int **returnColumnSizes = (int **)malloc(sizeof(int *) * base);

    int **ret = fourSum(nums, 4, 0, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("\n");
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d, ", ret[i][j]);
        }
    }

    return 0;
}
