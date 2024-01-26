/*
 * @lc app=leetcode id=78 lang=c
 *
 * [78] Subsets
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    if (numsSize == 0)
    {
        *returnSize = 1;
        *returnColumnSizes = (int *)malloc(sizeof(int));
        (*returnColumnSizes)[0] = 0;
        int **sub_sets = (int **)malloc(sizeof(int *));
        sub_sets[0] = NULL;
        return sub_sets;
    }

    int pre_sub_size = 2, cur_sub_size = 0;
    int *pre_sub_sets_col_size = (int *)malloc(sizeof(int) * pre_sub_size), *cur_sub_sets_col_size = NULL;
    int **pre_sub_sets = (int **)malloc(sizeof(int *) * pre_sub_size), **cur_sub_sets = NULL;

    pre_sub_sets_col_size[0] = 0;
    pre_sub_sets_col_size[1] = 1;

    pre_sub_sets[0] = NULL;
    pre_sub_sets[1] = (int *)malloc(sizeof(int) * 1);
    pre_sub_sets[1][0] = nums[0];

    for (int i = 1; i < numsSize; i++)
    {
        cur_sub_size = pre_sub_size * 2;
        cur_sub_sets_col_size = (int *)malloc(sizeof(int) * cur_sub_size);
        cur_sub_sets = (int **)malloc(sizeof(int *) * cur_sub_size);
        memcpy(cur_sub_sets_col_size, pre_sub_sets_col_size, sizeof(int) * pre_sub_size);
        memcpy(cur_sub_sets + 1, pre_sub_sets + 1, sizeof(int *) * (pre_sub_size - 1));
        for (int j = 0; j < pre_sub_size; j++)
        {
            if (j == 0)
            {
                cur_sub_sets_col_size[pre_sub_size] = 1;
                cur_sub_sets[pre_sub_size] = (int *)malloc(sizeof(int));
                cur_sub_sets[pre_sub_size][0] = nums[i];
            }
            else
            {
                cur_sub_sets_col_size[pre_sub_size + j] = pre_sub_sets_col_size[j] + 1;
                cur_sub_sets[pre_sub_size + j] = (int *)malloc(sizeof(int) * cur_sub_sets_col_size[pre_sub_size + j]);
                memcpy(cur_sub_sets[pre_sub_size + j], pre_sub_sets[j], sizeof(int) * pre_sub_sets_col_size[j]);
                cur_sub_sets[pre_sub_size + j][cur_sub_sets_col_size[pre_sub_size + j] - 1] = nums[i];
            }
        }
        free(pre_sub_sets_col_size);
        free(pre_sub_sets);
        pre_sub_sets_col_size = cur_sub_sets_col_size;
        pre_sub_sets = cur_sub_sets;
        pre_sub_size = cur_sub_size;
    }
    *returnSize = pre_sub_size;
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * (*returnSize));
    memcpy(*returnColumnSizes, pre_sub_sets_col_size, sizeof(int) * (*returnSize));
    return pre_sub_sets;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int nums[3] = {1, 2, 3};
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    subsets(nums, 3, returnSize, returnColumnSizes);
    return 0;
}
