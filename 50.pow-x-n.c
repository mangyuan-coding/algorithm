/*
 * @lc app=leetcode id=50 lang=c
 *
 * [50] Pow(x, n)
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

double myPow(double x, int n)
{
    if (n == 0)
    {
        return 1;
    }

    if (x == 0)
    {
        return n == 1 ? 0 : 1;
    }

    if (x == 1)
    {
        return x;
    }

    if (x == -1)
    {
        return n == INT32_MIN ? 1 : x < 0 && (n % 2 != 0) ? -1
                                                          : 1;
    }

    bool n_negative = n < 0;
    bool min_int = n == INT32_MIN;
    if (min_int)
    {
        n = INT32_MAX;
    }
    else
    {
        n = n_negative ? -n : n;
    }
    double *x_n_pow = (double *)malloc(sizeof(double) * 32);

    bool pow_negative = x < 0 && (n % 2 != 0);
    if (min_int)
    {
        pow_negative = false;
    }

    long reduced_n = 2;
    int idx = 1;
    x_n_pow[0] = pow_negative ? -x : x;
    for (; reduced_n < n; reduced_n *= 2, idx++)
    {
        x_n_pow[idx] = x_n_pow[idx - 1] * x_n_pow[idx - 1];
    }

    reduced_n /= 2;
    idx--;

    double pow = x_n_pow[idx];

    long remain_n = n - reduced_n;
    if (min_int)
    {
        remain_n += 1;
    }
    while (remain_n > 0)
    {
        if (remain_n == reduced_n)
        {
            pow *= x_n_pow[idx];
            break;
        }
        if (remain_n > reduced_n)
        {
            pow *= x_n_pow[idx];
            remain_n -= reduced_n;
        }
        else
        {
            reduced_n /= 2;
            idx--;
        }
    }

    pow = n_negative ? 1 / pow : pow;

    return pow_negative ? -pow : pow;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%f", myPow(-1.00000, -2147483648));
    return 0;
}
