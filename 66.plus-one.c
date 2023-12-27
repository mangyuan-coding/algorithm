/*
 * @lc app=leetcode id=66 lang=c
 *
 * [66] Plus One
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int *plusOne(int *digits, int digitsSize, int *returnSize)
{
    int *ret = (int *)malloc(sizeof(int) * (digitsSize + 1));
    int carry = 1;
    for (int i = digitsSize - 1; i >= 0; i--)
    {
        int num = digits[i] + carry;
        if (num > 9)
        {
            carry = num / 10;
            ret[i + 1] = num % 10;
        }
        else
        {
            carry = 0;
            ret[i + 1] = num;
        }
    }

    if (carry > 0)
    {
        ret[0] = carry;
        *returnSize = digitsSize + 1;
        return ret;
    }

    *returnSize = digitsSize;
    return ret + 1;
}
// @lc code=end
