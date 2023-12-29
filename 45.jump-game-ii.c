/*
 * @lc app=leetcode id=45 lang=c
 *
 * [45] Jump Game II
 */

// @lc code=start
#include <stdlib.h>

int jump(int *nums, int numsSize)
{
    int *trace = (int *)malloc(sizeof(int) * numsSize);
    int cur_step = 0;

    int min_step = numsSize;

    int idx = 0;
    while (1)
    {
        int num = nums[idx];
        if (num + idx > numsSize)
        {
            if (cur_step + 1 < min_step)
            {
                min_step = cur_step + 1;
            }

            while (cur_step >= 0)
            {
                if (trace[cur_step] > 1)
                {
                    trace[cur_step]--;
                    idx--;
                    break;
                }
                idx -= trace[cur_step];
                cur_step--;
            }
            if (cur_step == 0 && trace[cur_step] == 0)
            {
                break;
            }
        }
        else
        {
            trace[cur_step++] = num;
            idx += num;
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
