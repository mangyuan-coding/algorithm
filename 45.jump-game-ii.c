/*
 * @lc app=leetcode id=45 lang=c
 *
 * [45] Jump Game II
 */

// @lc code=start
#include <stdlib.h>

int jump(int *nums, int numsSize)
{
    int *each_step_distance = (int *)malloc(sizeof(int) * numsSize);
    int step = 0;

    int min_step = numsSize;

    int idx = 0;
    while (1)
    {
        if (idx >= numsSize - 1)
        {
            if (step < min_step)
            {
                min_step = step;
            }

            // back
            // last step distance == 1
            while (each_step_distance[step - 1] == 1 && step > 0)
            {
                idx -= each_step_distance[step - 1];
                each_step_distance[step - 1] = 0;
                step--;
            }

            // no route
            if (step == 0)
            {
                return min_step;
            }

            // distance - 1
            each_step_distance[step - 1]--;
            idx--;
        }
        else
        {
            // step to next
            int distance = nums[idx];
            step++;
            each_step_distance[step - 1] = distance;
            idx += distance;
        }
    }

    return min_step;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums[] = {2, 3, 1, 1, 4};
    printf("%d", jump(nums, 5));
    return 0;
}
