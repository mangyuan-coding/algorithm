/*
 * @lc app=leetcode id=7 lang=c
 *
 * [7] Reverse Integer
 */

// @lc code=start
#include <stdbool.h>
#include <stdint.h>

int reverse(int x)
{
    int ret = 0;

    while (x != 0)
    {
        if (ret > INT32_MAX / 10 || INT32_MIN / 10 > ret)
        {
            return 0;
        }

        ret = ret * 10 + x % 10;

        x = x / 10;
    }

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("ret is %d", reverse(-2147483648));
    return 0;
}
