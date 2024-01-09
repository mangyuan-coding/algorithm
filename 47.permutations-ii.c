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

int compare(const void *a, const void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
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

    qsort(nums, numsSize, sizeof(int), compare);

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
            if (same_num_size == 1)
            {
                ret = (int **)malloc(sizeof(int *) * (pre_size * (i + 1)));
                for (int j = 0; j < pre_size; j++)
                {
                    for (int k = 0; k <= i; k++)
                    {
                        (*returnSize)++;
                        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * (i + 1));
                        ret[*returnSize - 1][k] = num;
                        if (k == 0)
                        {
                            memcpy(ret[*returnSize - 1] + 1, pre[j], sizeof(int) * i);
                        }
                        else if (k == i)
                        {
                            memcpy(ret[*returnSize - 1], pre[j], sizeof(int) * i);
                        }
                        else
                        {
                            memcpy(ret[*returnSize - 1], pre[j], sizeof(int) * k);
                            memcpy(ret[*returnSize - 1] + k + 1, pre[j] + k, sizeof(int) * (i - k));
                        }
                    }
                }
            }
            else
            {
                int base = 1000;
                ret = (int **)malloc(sizeof(int *) * base);
                struct distribution *n_distribution = distribute(same_num_size);
                struct distribution cur_distribution = n_distribution[same_num_size - 1];

                for (int idx_of_group = 0; idx_of_group < cur_distribution.group_size; idx_of_group++)
                {
                    struct group cur_group = cur_distribution.groups[idx_of_group];

                    int total_num_size = i + 1;

                    for (int idx_of_pre = 0; idx_of_pre < pre_size; idx_of_pre++)
                    {
                        int *pre_nums = pre[idx_of_pre];

                        int total_positions = i - same_num_size + 1 + cur_group.num_size;
                        int idx_of_pre_nums = i - same_num_size;
                        int idx_of_cur_group = cur_group.num_size - 1;
                        int idx_of_position = total_positions - 1;

                        // 1 == pre, 0 == group
                        int *trace = (int *)malloc(sizeof(int) * total_positions);

                        int idx_of_ret_nums = total_num_size - 1;
                        (*returnSize)++;
                        ret[*returnSize - 1] = (int *)malloc(sizeof(int) * total_num_size);

                        while (1)
                        {
                            if (idx_of_position >= 0)
                            {
                                if (idx_of_pre_nums >= 0)
                                {
                                    ret[*returnSize - 1][idx_of_ret_nums--] = pre[idx_of_pre][idx_of_pre_nums];
                                    trace[idx_of_position] = 1;
                                    idx_of_position--;
                                    idx_of_pre_nums--;
                                }
                                else
                                {
                                    for (int idx_of_nums = 0; idx_of_nums < cur_group.nums[idx_of_cur_group]; idx_of_nums++)
                                    {
                                        ret[*returnSize - 1][idx_of_ret_nums--] = num;
                                    }
                                    trace[idx_of_position] = 0;
                                    idx_of_position--;
                                    idx_of_cur_group--;
                                }
                            }
                            else
                            {
                                while (idx_of_position < total_positions - 1)
                                {
                                    if (trace[idx_of_position + 1] == 1 && idx_of_cur_group >= 0)
                                    {
                                        idx_of_position++;
                                        idx_of_ret_nums++;
                                        idx_of_pre_nums++;
                                        break;
                                    }
                                    else
                                    {
                                        if (trace[idx_of_position + 1] == 0)
                                        {
                                            idx_of_ret_nums += cur_group.nums[idx_of_cur_group + 1];
                                            idx_of_cur_group++;
                                        }
                                        else
                                        {
                                            idx_of_ret_nums++;
                                            idx_of_pre_nums++;
                                        }
                                        idx_of_position++;
                                    }
                                }
                                if (idx_of_position == total_positions - 1 && trace[idx_of_position] == 0)
                                {
                                    break;
                                }
                                (*returnSize)++;
                                if (*returnSize == base)
                                {
                                    base *= 1.5;
                                    ret = (int **)realloc(ret, sizeof(int *) * base);
                                }
                                ret[*returnSize - 1] = (int *)malloc(sizeof(int) * total_num_size);
                                memcpy(ret[*returnSize - 1], ret[*returnSize - 2], sizeof(int) * (i + 1));

                                for (int idx_of_nums = 0; idx_of_nums < cur_group.nums[idx_of_cur_group]; idx_of_nums++)
                                {
                                    ret[*returnSize - 1][idx_of_ret_nums--] = num;
                                }
                                trace[idx_of_position] = 0;
                                idx_of_position--;
                                idx_of_cur_group--;
                            }
                        }
                    }
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
    int nums[8] = {-1, 2, -1, 2, 1, -1, 2, 1};
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int **ret = permuteUnique(nums, 8, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("i is %d, [", i);
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d,", ret[i][j]);
        }
        printf("] \n");
    }

    return 0;
}