/*
 * @lc app=leetcode id=47 lang=c
 *
 * [47] Permutations II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

typedef struct distribution
{
    int group_size;
    struct group *groups;
} distribution;

typedef struct group
{
    int num_size;
    int *nums;
} group;

struct distribution **distributions = NULL;
int n = 0;

struct distribution *distribute(int target_n)
{
    if (n == 0)
    {
        distributions = (struct distribution **)malloc(sizeof(struct distribution *));
        distributions[0] = (struct distribution *)malloc(sizeof(struct distribution));
        distributions[0][0].group_size = 1;
        distributions[0][0].groups = (struct group *)malloc(sizeof(struct group));
        distributions[0][0].groups[0].num_size = 1;
        distributions[0][0].groups[0].nums = (int *)malloc(sizeof(int));
        distributions[0][0].groups[0].nums[0] = 1;
        n++;
    }
    if (target_n > n)
    {
        distributions = (struct distribution **)realloc(distributions, sizeof(struct distribution *) * target_n);
        for (int num_size = n + 1; num_size <= target_n; num_size++)
        {
            distributions[num_size - 1] = (struct distribution *)malloc(sizeof(struct distribution) * target_n);

            for (int position_size = 1; position_size <= target_n && num_size >= position_size; position_size++)
            {
                int remain_position = position_size - 1;
                if (remain_position < 1)
                {
                    distributions[num_size - 1][position_size - 1].group_size = 1;
                    distributions[num_size - 1][position_size - 1].groups = (struct group *)malloc(sizeof(struct group));

                    distributions[num_size - 1][position_size - 1].groups[0].num_size = 1;
                    distributions[num_size - 1][position_size - 1].groups[0].nums = (int *)malloc(sizeof(int));
                    distributions[num_size - 1][position_size - 1].groups[0].nums[0] = num_size;
                    continue;
                }
                else
                {
                    int cur_group_size = 0;
                    for (int first_position_num_size = 1; first_position_num_size <= num_size - position_size + 1; first_position_num_size++)
                    {
                        int remain_num_size = num_size - first_position_num_size;
                        cur_group_size += distributions[remain_num_size - 1][remain_position - 1].group_size;
                    }
                    distributions[num_size - 1][position_size - 1].group_size = cur_group_size;
                    distributions[num_size - 1][position_size - 1].groups = (struct group *)malloc(sizeof(struct group) * cur_group_size);

                    int idx_of_group = 0;
                    for (int first_position_num_size = 1; first_position_num_size <= num_size - position_size + 1; first_position_num_size++)
                    {
                        // f[m][n] = {first_position_num_size, f[m - first_position_num_size][n - 1]...}
                        for (int idx_of_remain_group = 0;
                             idx_of_remain_group < distributions[num_size - first_position_num_size - 1][remain_position - 1].group_size;
                             idx_of_remain_group++)
                        {
                            struct group pre_group = distributions[num_size - first_position_num_size - 1][remain_position - 1].groups[idx_of_remain_group];

                            distributions[num_size - 1][position_size - 1].groups[idx_of_group].num_size = pre_group.num_size + 1;
                            distributions[num_size - 1][position_size - 1].groups[idx_of_group].nums = (int *)malloc(sizeof(int) * distributions[num_size - 1][position_size - 1].groups[idx_of_group].num_size);
                            distributions[num_size - 1][position_size - 1].groups[idx_of_group].nums[0] = first_position_num_size;

                            memcpy(distributions[num_size - 1][position_size - 1].groups[idx_of_group].nums + 1, pre_group.nums, sizeof(int) * pre_group.num_size);

                            idx_of_group++;
                        }
                    }
                }
            }
        }
    }

    return distributions[target_n - 1];
}

int **build_trace(int a_size, int b_size)
{
    int size = a_size + b_size;
    int **trace = (int **)malloc(sizeof(int *) * size);
    int trace_size = 1;

    int idx_a = a_size - 1, idx_b = b_size - 1, idx = size - 1;

    while (1)
    {
        if (idx > 0)
        {
            if (idx_a >= 0)
            {
                trace[trace_size - 1][idx--] = 1;
                idx_a--;
            }
            else
            {
                trace[trace_size - 1][idx--] = 0;
                idx_b--;
            }
        }
        else
        {
            
        }
    }
}

int **permuteUnique(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    if (numsSize == 0)
    {
        return NULL;
    }
    int **ret = (int **)malloc(sizeof(int *));
    *returnColumnSizes = (int *)malloc(sizeof(int));
    *returnSize = 1;
    (*returnColumnSizes)[0] = 1;
    ret[0] = (int *)malloc(sizeof(int));
    ret[0][0] = nums[0];
    if (numsSize == 1)
    {
        return ret;
    }

    int **pre = NULL;
    int pre_size = 0;

    *returnSize = 0;
    int same_num_size = 1;
    for (int i = 0; i < numsSize; i++)
    {
        if (i < numsSize - 1 && nums[i] == nums[i + 1])
        {
            same_num_size++;
            continue;
        }

        int num = nums[i];
        if (pre_size == 0)
        {
            (*returnSize)++;
            ret[*returnSize - 1] = (int *)malloc(sizeof(int) * (same_num_size));
            for (int g = 0; g < same_num_size; g++)
            {
                ret[*returnSize - 1][g] = num;
            }
        }
        else
        {
            *returnSize = 0;
            struct distribution *n_distribution = distribute(same_num_size);

            for (int postion_size = 1; postion_size <= same_num_size; postion_size++)
            {
                struct distribution cur_distribution = n_distribution[postion_size - 1];

                for (int idx_of_group = 0; idx_of_group < cur_distribution.group_size; idx_of_group++)
                {
                    struct group cur_group = cur_distribution.groups[idx_of_group];

                    int total_num_size = pre_size;
                    for (int idx_of_cur_group = 0; idx_of_cur_group < cur_group.num_size; idx_of_cur_group++)
                    {
                        total_num_size += cur_group.nums[idx_of_cur_group];
                    }

                    int idx_of_position = cur_group.num_size + pre_size - 1;
                    int idx_of_cur_group = cur_group.num_size - 1;
                    int idx_of_pre = pre_size - 1;

                    // 1 == pre, 0 == group
                    int *trace = (int *)malloc(sizeof(int) * cur_group.num_size + pre_size);
                }
            }
        }
        if (pre != NULL)
        {
            free(pre);
        }
        pre = ret;
        pre_size = *returnSize;
        same_num_size = 1;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }

    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // int nums[4] = {2, 2, 1, 1};
    // int *returnSize = (int *)malloc(sizeof(int));
    // int **returnColumnSizes = (int **)malloc(sizeof(int *));
    // int **ret = permuteUnique(nums, 4, returnSize, returnColumnSizes);
    // for (int i = 0; i < *returnSize; i++)
    // {
    //     printf("i is %d, [", i);
    //     for (int j = 0; j < (*returnColumnSizes)[i]; j++)
    //     {
    //         printf("%d,", ret[i][j]);
    //     }
    //     printf("] \n");
    // }

    int n = 4;
    struct distribution *n_distribution = distribute(n);

    for (int position = 1; position <= n; position++)
    {
        struct distribution cur_distribution = n_distribution[position - 1];
        printf("cur position is %d [ ", position);
        for (int idx_of_groups = 0; idx_of_groups < cur_distribution.group_size; idx_of_groups++)
        {
            struct group cur_group = cur_distribution.groups[idx_of_groups];
            printf("cur group is %d [ ", idx_of_groups + 1);
            for (int idx_of_nums = 0; idx_of_nums < cur_group.num_size; idx_of_nums++)
            {
                printf("%d", cur_group.nums[idx_of_nums]);
                if (idx_of_nums != cur_group.num_size - 1)
                {
                    printf(",");
                }
            }

            printf(" ] ,");
        }
        printf(" ] \n");
    }

    return 0;
}