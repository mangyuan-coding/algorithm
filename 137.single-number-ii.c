/*
 * @lc app=leetcode.cn id=137 lang=c
 *
 * [137] Single Number II
 */

#include <stdio.h>

// @lc code=start
#include <stdint.h>
#include <stdbool.h>

const int MASK = 0x1;

int singleNumber(int *nums, int numsSize)
{
    int bit_size[32];
    for (int i = 0; i < 32; i++)
    {
        bit_size[i] = 0;
    }

    int positive_size = 0, min_size = 0;
    for (int i = 0; i < numsSize; i++)
    {
        int num = nums[i];
        if (num < 0)
        {
            positive_size++;
            if (num == INT32_MIN)
            {
                num = INT32_MAX;
                min_size++;
            }
            else
            {
                num = -num;
            }
        }

        for (int j = 31; j >= 0; j--)
        {
            if (num & MASK > 0)
            {
                bit_size[j]++;
            }
            num >>= 1;
        }
    }

    if (min_size % 3 == 1)
    {
        return INT32_MIN;
    }

    int num = 0;
    for (int i = 0; i < 32; i++)
    {
        if (bit_size[i] % 3 == 1)
        {
            num++;
        }
        if (num != 0 && i != 31)
        {
            num <<= 1;
        }
    }

    return positive_size % 3 == 1 ? -num : num;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int num = 1;
    for (int i = 1; i < 32; i++)
    {
    }

    return 0;
}
