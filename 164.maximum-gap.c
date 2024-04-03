/*
 * @lc app=leetcode.cn id=164 lang=c
 *
 * [164] Maximum Gap
 */

// @lc code=start
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int maximumGap(int *nums, int numsSize)
{
    if (numsSize < 2)
    {
        return 0;
    }
    int maxVal = INT_MIN, minVal = INT_MAX;
    for (int i = 0; i < numsSize; ++i)
    {
        maxVal = fmax(maxVal, nums[i]);
        minVal = fmin(minVal, nums[i]);
    }
    int d = fmax(1, (maxVal - minVal) / (numsSize - 1));
    int bucketSize = (maxVal - minVal) / d + 1;

    int bucket[bucketSize][2];
    memset(bucket, -1, sizeof(bucket)); // 存储 (桶内最小值，桶内最大值) 对，(-1, -1) 表示该桶是空的
    for (int i = 0; i < numsSize; i++)
    {
        int idx = (nums[i] - minVal) / d;
        if (bucket[idx][0] == -1)
        {
            bucket[idx][0] = bucket[idx][1] = nums[i];
        }
        else
        {
            bucket[idx][0] = fmin(bucket[idx][0], nums[i]);
            bucket[idx][1] = fmax(bucket[idx][1], nums[i]);
        }
    }

    int ret = 0;
    int prev = -1;
    for (int i = 0; i < bucketSize; i++)
    {
        if (bucket[i][0] == -1)
            continue;
        if (prev != -1)
        {
            ret = fmax(ret, bucket[i][0] - bucket[prev][1]);
        }
        prev = i;
    }
    return ret;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int nums[3] = {1, 3, 100};
    int gap = maximumGap(nums, 3);
    return 0;
}
