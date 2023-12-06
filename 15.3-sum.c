/*
 * @lc app=leetcode id=15 lang=c
 *
 * [15] 3Sum
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int base = 100;
    int **ret = (int **)malloc(sizeof(int *) * base);
    *returnColumnSizes = (int *)malloc(sizeof(int) * base);
    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), int_cmp);

    for (int i = 0; i < numsSize; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        if (nums[i] > 0)
        {
            break;
        }
        int left = i + 1, right = numsSize - 1;
        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0)
            {
                if (*returnSize == base)
                {
                    base = base * 1.5;
                    ret = (int **)realloc(ret, sizeof(int *) * base);
                    *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * base);
                }
                ret[*returnSize] = (int *)malloc(sizeof(int) * 3);
                ret[*returnSize][0] = nums[i];
                ret[*returnSize][1] = nums[left];
                ret[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                *returnSize += 1;
                left++;
                while (left < right && nums[left] == nums[left - 1])
                {
                    left++;
                }
            }
            else if (sum > 0)
            {
                right--;
                while (left < right && nums[right] == nums[right + 1])
                {
                    right--;
                }
            }
            else
            {
                left++;
                while (left < right && nums[left] == nums[left - 1])
                {
                    left++;
                }
            }
        }
    }
    return ret;
}
// @lc code=end
// #include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {-13, 5, 13, 12, -2, -11, -1, 12, -3, 0, -3, -7, -7, -5, -3, -15, -2, 14, 14, 13, 6, -11, -11, 5, -15, -14, 5, -5, -2, 0, 3, -8, -10, -7, 11, -5, -10, -5, -7, -6, 2, 5, 3, 2, 7, 7, 3, -10, -2, 2, -12, -11, -1, 14, 10, -9, -15, -8, -7, -9, 7, 3, -2, 5, 11, -13, -15, 8, -3, -7, -12, 7, 5, -2, -6, -3, -10, 4, 2, -5, 14, -3, -1, -10, -3, -14, -4, -3, -7, -4, 3, 8, 14, 9, -2, 10, 11, -10, -4, -15, -9, -1, -1, 3, 4, 1, 8, 1};
    printf("nums's len is %d", sizeof(nums) / sizeof(int));
    int base = 108;
    int *returnSize = (int *)malloc(sizeof(int) * base);
    int **returnColumnSizes = (int **)malloc(sizeof(int *) * base);

    int **ret = threeSum(nums, 108, returnSize, returnColumnSizes);
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
