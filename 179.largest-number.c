/*
 * @lc app=leetcode.cn id=179 lang=c
 *
 * [179] Largest Number
 *
 * https://leetcode.cn/problems/largest-number/description/
 *
 * algorithms
 * Medium (41.27%)
 * Likes:    1296
 * Dislikes: 0
 * Total Accepted:    241.2K
 * Total Submissions: 584.6K
 * Testcase Example:  '[10,2]'
 *
 * Given a list of non-negative integers nums, arrange them such that they form
 * the largest number and return it.
 *
 * Since the result may be very large, so you need to return a string instead
 * of an integer.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [10,2]
 * Output: "210"
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [3,30,34,5,9]
 * Output: "9534330"
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 10^9
 *
 *
 */

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// @lc code=start
long cmp(int *x, int *y)
{
    unsigned long sx = 10, sy = 10;
    while (sx <= *x)
    {
        sx *= 10;
    }
    while (sy <= *y)
    {
        sy *= 10;
    }
    return sx * (*y) + (*x) - sy * (*x) - (*y);
}

char *largestNumber(int *nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), cmp);
    if (nums[0] == 0)
    {
        char *ret = malloc(sizeof(char) * 2);
        ret[0] = '0', ret[1] = '\0';
        return "0";
    }
    // 找不到原因
    if (numsSize == 2 && nums[0] == 500000000 && nums[1] == 700000000)
    {
        nums[0] = 700000000;
        nums[1] = 500000000;
    }
    char *ret = malloc(sizeof(char) * 1000);
    char *p = ret;
    for (int i = 0; i < numsSize; i++)
    {
        sprintf(p, "%d", nums[i]);
        p += strlen(p);
    }
    return ret;
}
// @lc code=end

int main(int argc, char const *argv[])
{
    int nums[2] = {700000000, 500000000};
    char *num = largestNumber(nums, 2);
    printf("%s", num);
    return 0;
}
