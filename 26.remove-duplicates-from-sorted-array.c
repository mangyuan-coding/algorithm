/*
 * @lc app=leetcode id=26 lang=c
 *
 * [26] Remove Duplicates from Sorted Array
 */

// @lc code=start
int removeDuplicates(int *nums, int numsSize)
{
    int left = 0, right = 1;

    while (right < numsSize)
    {
        if (nums[left] < nums[right])
        {
            if (right > left + 1)
            {
                nums[left + 1] = nums[right];
            }
            left++;
        }
        right++;
    }

    return left + 1;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    int ret = removeDuplicates(nums, 10);

    printf("ret is %d \n", ret);

    for (int i = 0; i < ret; i++)
    {
        printf("nums[%d] is %d \n", i, nums[i]);
    }

    return 0;
}
