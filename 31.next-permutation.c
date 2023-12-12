/*
 * @lc app=leetcode id=31 lang=c
 *
 * [31] Next Permutation
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void nextPermutation(int *nums, int numsSize)
{
    int right = numsSize - 1;
    int target_left = -1;
    int target_right = numsSize;
    for (; right > target_left;)
    {
        int left = right - 1;
        for (; left > target_left;)
        {
            if (nums[left] < nums[right])
            {
                target_right = right;
                break;
            }
            left--;
        }

        if (left > target_left)
        {
            target_left = left;
        }
        right--;
    }

    if (target_left == -1 && target_right == numsSize)
    {
        qsort(nums, numsSize, sizeof(int), int_cmp);
        return;
    }

    int tmp = nums[target_left];
    nums[target_left] = nums[target_right];
    nums[target_right] = tmp;
    qsort(nums + target_left + 1, numsSize - target_left - 1, sizeof(int), int_cmp);
}
// @lc code=end

int main(int argc, char const *argv[])
{
    int nums[] = {1, 3, 2};
    nextPermutation(nums, 3);
    for (int i = 0; i < 3; i++)
    {
        printf("i is %d, value is %d \n", i, nums[i]);
    }

    return 0;
}
