/*
 * @lc app=leetcode id=16 lang=c
 *
 * [16] 3Sum Closest
 */

// @lc code=start
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int threeSumClosest(int *nums, int numsSize, int target)
{
    qsort(nums, numsSize, sizeof(int), int_cmp);

    int closest = INT_MAX, closest_sum;
    for (int i = 0; i < numsSize; i++)
    {

        for (int j = i + 1; j < numsSize; j++)
        {
            int dur, sum;
            for (int k = j + 1; k < numsSize; k++)
            {
                sum = nums[i] + nums[j] + nums[k];
                dur = fabs(sum - target);

                if (k < numsSize - 1)
                {
                    int next_dur = fabs(nums[i] + nums[j] + nums[k + 1] - target);
                    if (next_dur > dur)
                    {
                        break;
                    }
                }
            }
            if (dur < closest)
            {
                closest = dur;
                closest_sum = sum;
            }
        }
    }

    return closest_sum;
}
// @lc code=end
// #include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {4, 0, 5, -5, 3, 3, 0, -4, -5};
    printf("nums's len is %d", sizeof(nums) / sizeof(int));
    printf("closest is %d", threeSumClosest(nums, 9, -2));
    return 0;
}
