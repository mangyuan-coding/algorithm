/*
 * @lc app=leetcode id=89 lang=c
 *
 * [89] Gray Code
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *grayCode(int n, int *returnSize)
{
    int *gray_codes = (int *)malloc(sizeof(int) * pow(2, n));
    *returnSize = 0;
    gray_codes[(*returnSize)++] = 0;
    gray_codes[(*returnSize)++] = 1;

    if (n == 1)
    {
        return gray_codes;
    }

    int pre_size, weight;
    for (int i = 2; i <= n; i++)
    {
        weight = pow(2, i - 1);
        pre_size = *returnSize;
        for (int idx = pre_size - 1; idx >= 0; idx--)
        {
            gray_codes[(*returnSize)++] = gray_codes[idx] + weight;
        }
    }

    return gray_codes;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("just test");
    int *returnSize = (int *)malloc(sizeof(int));
    grayCode(1, returnSize);
    return 0;
}
