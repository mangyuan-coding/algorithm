/*
 * @lc app=leetcode id=55 lang=c
 *
 * [55] Jump Game
 */
#include <stdbool.h>
// @lc code=start
#include <stdlib.h>

bool canJump(int *nums, int numsSize)
{
    if (numsSize == 1)
    {
        return true;
    }

    bool *landable_idxes = (bool *)malloc(sizeof(bool) * numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        landable_idxes[i] = false;
    }

    landable_idxes[0] = true;

    int farthest_idx = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (landable_idxes[i] && i + nums[i] > farthest_idx)
        {
            if (i + nums[i] >= numsSize - 1)
            {
                return true;
            }
            for (int j = i + 1; j <= i + nums[i]; j++)
            {
                landable_idxes[j] = true;
            }
            farthest_idx = i + nums[i];
        }
    }

    return false;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *nums = (int *)malloc(sizeof(int) * 2);
    nums[0] = 2;
    nums[1] = 0;
    printf("%d", canJump(nums, 2));
    return 0;
}
