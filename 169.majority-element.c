/*
 * @lc app=leetcode id=169 lang=c
 *
 * [169] Majority Element
 */

// @lc code=start
#include <stdlib.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int majorityElement(int *nums, int numsSize)
{
    if (numsSize <= 2)
    {
        return nums[0];
    }

    int threshold = numsSize % 2 == 0 ? numsSize / 2 : numsSize / 2 + 1;
    qsort(nums, numsSize, sizeof(int), int_cmp);

    for (int i = 0, j = 1; j < numsSize;)
    {
        if (nums[j] == nums[i])
        {
            j++;
        }
        else
        {
            if (j - i >= threshold)
            {
                return nums[i];
            }
            else
            {
                i = j;
                j = i + 1;
            }
        }
    }

    return nums[numsSize - 1];
}
// @lc code=end
