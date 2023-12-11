/*
 * @lc app=leetcode id=29 lang=c
 *
 * [29] Divide Two Integers
 */

// @lc code=start
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

int num_of_leading_zeros(uint32_t num)
{
    int n = 32;
    if (num >= 1 << 16)
    {
        n -= 16;
        num >>= 16;
    }
    if (num >= 1 << 8)
    {
        n -= 8;
        num >>= 8;
    }
    if (num >= 1 << 4)
    {
        n -= 4;
        num >>= 4;
    }
    if (num >= 1 << 2)
    {
        n -= 2;
        num >>= 2;
    }
    return n - (num >> 1);
}

int diff_num_of_leading_zeros(uint32_t num1, uint32_t num2)
{
    return abs(num_of_leading_zeros(num1) - num_of_leading_zeros(num2));
}

int divide(int dividend, int divisor)
{
    bool negative = (dividend ^ divisor) < 0;
    uint32_t non_nega_dividend = dividend == INT32_MIN ? (uint32_t)INT32_MAX + 1 : dividend > 0 ? (uint32_t)dividend
                                                                                                : (uint32_t)-dividend,
             non_nega_divisor = divisor == INT32_MIN ? (uint32_t)INT32_MAX + 1 : divisor > 0 ? (uint32_t)divisor
                                                                                             : (uint32_t)-divisor;

    if (non_nega_divisor > non_nega_dividend)
    {
        return 0;
    }

    if (divisor == 1)
    {
        return dividend;
    }

    if (divisor == -1)
    {
        return dividend == INT32_MIN ? INT32_MAX : -dividend;
    }

    int quotient = 0;
    for (int diff = diff_num_of_leading_zeros(non_nega_dividend, non_nega_divisor); diff >= 0; diff--)
    {
        int r = non_nega_divisor << diff;
        if (r <= non_nega_dividend)
        {
            quotient |= (1 << diff);
            non_nega_dividend -= r;
        }
    }

    return negative ? -quotient : quotient;
}
// @lc code=end
#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    // printf("ret is %d", divide(-2147483648, -1));
    printf("bit len is %d", divide(10, 3));
    return 0;
}
