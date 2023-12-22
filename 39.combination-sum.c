/*
 * @lc app=leetcode id=39 lang=c
 *
 * [39] Combination Sum
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

// [x1, x2, x3, x4, x5, ..., xn]
// a*x1 + b*x2 + c*x3 + ..., m*xn = target
int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
    int base = 10;
    *returnSize = 0;
    int **ret = (int **)malloc(sizeof(int *) * base);

    int *factors = (int *)malloc(sizeof(int) * candidatesSize);
    for (int i = 0; i < candidatesSize; i++)
    {
        factors[i] = 0;
    }

    int idx = 0;
    int sum = 0;
    int sum_fac = 0;
    while (1)
    {
        int factor = factors[idx];
        sum_fac += factor;
        sum += factor * candidates[idx];

        if (sum >= target)
        {
            if (sum == target)
            {
                if (*returnSize > base)
                {
                    base *= 1.5;
                    ret = (int **)realloc(ret, sizeof(int *) * base);
                }

                ret[(*returnSize)++] = (int *)malloc(sizeof(int) * sum_fac);
                *(returnColumnSizes[*returnSize - 1]) = 0;
                for (int i = 0; i <= idx; i++)
                {
                    for (int j = 0; j < factors[i]; j++)
                    {
                        ret[*returnSize - 1][(*(returnColumnSizes[*returnSize - 1]))++] = candidates[i];
                    }
                }
            }
            if (idx == 0)
            {
                break;
            }
            sum_fac -= factor;
            sum -= factor * candidates[idx];
            factors[idx] = 0;
            sum_fac -= factors[idx - 1];
            sum -= factors[idx - 1] * candidates[idx - 1];
            factors[--idx]++;
        }
        else
        {
            if (idx == candidatesSize - 1)
            {
                factors[idx]++;
            }
            else
            {
                idx++;
            }
        }
    }
    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int candidates[] = {2, 3, 6, 7};
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *) * 2);
    returnColumnSizes[0] = (int *)malloc(sizeof(int));
    returnColumnSizes[1] = (int *)malloc(sizeof(int));
    int **ret = combinationSum(candidates, 4, 7, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("ret is [");
        for (int j = 0; j < returnColumnSizes[0][i]; j++)
        {
            printf("%d,", ret[i][j]);
        }
        printf("] \n");
    }

    return 0;
}
