/*
 * @lc app=leetcode id=45 lang=c
 *
 * [45] Jump Game II
 */

// @lc code=start
#include <stdlib.h>

int jump(int *nums, int numsSize)
{

    int *each_min_step = (int *)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        each_min_step[i] = numsSize;
    }

    each_min_step[0] = 0;

    for (int i = 0; i < numsSize; i++)
    {
        int cur_min_step = each_min_step[i];
        int max_distance = nums[i];
        for (int step_distance = 1; step_distance <= max_distance; step_distance++)
        {
            if (i + step_distance >= numsSize)
            {
                break;
            }
            if (each_min_step[i + step_distance] > cur_min_step + 1)
            {
                each_min_step[i + step_distance] = cur_min_step + 1;
            }
        }
    }

    return each_min_step[numsSize - 1];
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {5, 6, 4, 4, 6, 9, 4, 4, 7, 4, 4, 8, 2, 6, 8, 1, 5, 9, 6, 5, 2, 7, 9, 7, 9, 6, 9, 4, 1, 6, 8, 8, 4, 4, 2, 0, 3, 8, 5};
    printf("%d", jump(nums, 39));
    return 0;
}
