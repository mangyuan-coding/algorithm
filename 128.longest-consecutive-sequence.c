/*
 * @lc app=leetcode.cn id=128 lang=c
 *
 * [128] Longest Consecutive Sequence
 */

// @lc code=start
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Bucket
{
    int num_size;

    int *nums;

    bool *idx_nums;
    int min_num;
    int max_num;
    int longest;
} Bucket;

int longestConsecutive(int *nums, int numsSize)
{
    if (numsSize == 0)
    {
        return 0;
    }
    if (numsSize == 1)
    {
        return 1;
    }
    int min = INT32_MAX;
    int max = INT32_MIN;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] < min)
        {
            min = nums[i];
        }
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }

    long distance = max - min;
    if (distance > numsSize * 10)
    {
        int bucket_size = numsSize + 1;
        long each_bucket_distance = distance / numsSize;
        struct Bucket **buckets = (struct Bucket **)malloc(sizeof(struct Bucket *) * bucket_size);
        for (int i = 0; i < bucket_size; i++)
        {
            buckets[i] = (struct Bucket *)malloc(sizeof(struct Bucket));
            buckets[i]->nums = (int *)malloc(sizeof(int) * numsSize);
            buckets[i]->num_size = 0;
            buckets[i]->max_num = INT32_MIN;
            buckets[i]->min_num = INT32_MAX;
        }

        for (int i = 0; i < numsSize; i++)
        {
            int bucket_idx = (nums[i] - min) / each_bucket_distance;
            buckets[bucket_idx]->nums[buckets[bucket_idx]->num_size++] = nums[i];
            if (nums[i] > buckets[bucket_idx]->max_num)
            {
                buckets[bucket_idx]->max_num = nums[i];
            }
            if (nums[i] < buckets[bucket_idx]->min_num)
            {
                buckets[bucket_idx]->min_num = nums[i];
            }
        }

        for (int bucket_idx = 0; bucket_idx < bucket_size; bucket_idx++)
        {
            if (buckets[bucket_idx]->num_size == 1)
            {
                buckets[bucket_idx]->longest = 1;
            }
            else if (buckets[bucket_idx]->num_size != 0)
            {
                int cur_distance = buckets[bucket_idx]->max_num - buckets[bucket_idx]->min_num;
                buckets[bucket_idx]->idx_nums = (bool *)malloc(sizeof(bool) * (cur_distance + 1));
                for (int i = 0; i <= cur_distance; i++)
                {
                    buckets[bucket_idx]->idx_nums[i] = false;
                }
                for (int i = 0; i < buckets[bucket_idx]->num_size; i++)
                {
                    buckets[bucket_idx]->idx_nums[buckets[bucket_idx]->nums[i] - buckets[bucket_idx]->min_num] = true;
                }
                int longest = 0, cur_longest = 0;
                for (int i = 0; i <= cur_distance; i++)
                {
                    if (buckets[bucket_idx]->idx_nums[i])
                    {
                        cur_longest++;
                    }
                    else
                    {
                        if (cur_longest > longest)
                        {
                            longest = cur_longest;
                        }
                        cur_longest = 0;
                    }
                }
                if (cur_longest > longest)
                {
                    longest = cur_longest;
                }
                buckets[bucket_idx]->longest = longest;
            }
        }

        int longest = 0;
        for (int bucket_idx = 0; bucket_idx < bucket_size; bucket_idx++)
        {
            if (buckets[bucket_idx]->num_size != 0)
            {
                if (longest < buckets[bucket_idx]->longest)
                {
                    longest = buckets[bucket_idx]->longest;
                }
            }
        }

        return longest;
    }
    else
    {
        bool *idx_nums = (bool *)malloc(sizeof(bool) * (distance + 1));
        for (int i = 0; i <= distance; i++)
        {
            idx_nums[i] = false;
        }

        for (int i = 0; i < numsSize; i++)
        {
            idx_nums[nums[i] - min] = true;
        }

        int longest = 0, cur_longest = 0;
        for (int i = 0; i <= distance; i++)
        {
            if (idx_nums[i])
            {
                cur_longest++;
            }
            else
            {
                if (cur_longest > longest)
                {
                    longest = cur_longest;
                }
                cur_longest = 0;
            }
        }
        if (cur_longest > longest)
        {
            longest = cur_longest;
        }
        return longest;
    }
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int *nums = (int *)malloc(sizeof(int) * 6);
    nums[0] = -1000000000;
    nums[1] = 1;
    nums[2] = 2;
    nums[3] = 3;
    nums[4] = 9;
    nums[5] = 1000000000;
    longestConsecutive(nums, 6);
    return 0;
}
