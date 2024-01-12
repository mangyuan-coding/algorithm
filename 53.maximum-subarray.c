/*
 * @lc app=leetcode id=53 lang=c
 *
 * [53] Maximum Subarray
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

struct sub_array
{
    int max_sum;
    int start;
    int end;
} sub_array;

int maxSubArray(int *nums, int numsSize)
{
    if (numsSize == 1)
    {
        return nums[0];
    }

    struct sub_array *subs = (struct sub_array *)malloc(sizeof(struct sub_array) * numsSize);
    subs[0].max_sum = nums[0];
    subs[0].start = 0;
    subs[0].end = 0;

    int continuous_max = nums[0];
    int continuous_start = 0;

    for (int i = 1; i < numsSize; i++)
    {
        if (continuous_max < 0)
        {
            continuous_max = nums[i];
            continuous_start = i;
        }
        else
        {
            continuous_max = continuous_max + nums[i];
        }

        if (nums[i] <= 0)
        {
            if (subs[i - 1].max_sum < nums[i])
            {
                subs[i].max_sum = nums[i];
                subs[i].start = i;
                subs[i].end = i;
            }
            else
            {
                subs[i].max_sum = subs[i - 1].max_sum;
                subs[i].start = subs[i - 1].start;
                subs[i].end = subs[i - 1].end;
            }
        }
        else
        {
            if (subs[i - 1].end == i - 1 && subs[i - 1].max_sum > 0)
            {
                subs[i].max_sum = subs[i - 1].max_sum + nums[i];
                subs[i].start = subs[i - 1].start;
                subs[i].end = i;
            }
            else
            {
                if (continuous_max > subs[i - 1].max_sum)
                {
                    subs[i].max_sum = continuous_max;
                    subs[i].start = continuous_start;
                    subs[i].end = i;
                }
                else
                {
                    subs[i].max_sum = subs[i - 1].max_sum;
                    subs[i].start = subs[i - 1].start;
                    subs[i].end = subs[i - 1].end;
                }
            }
        }
    }
    return subs[numsSize - 1].max_sum;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *nums = (int *)malloc(sizeof(int) * 2);
    nums[0] = -2;
    nums[1] = 1;
    printf("%d", maxSubArray(nums, 2));

    return 0;
}
