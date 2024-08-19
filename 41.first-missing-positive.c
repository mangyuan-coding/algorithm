/*
 * @lc app=leetcode.cn id=41 lang=c
 *
 * [41] First Missing Positive
 *
 * https://leetcode.cn/problems/first-missing-positive/description/
 *
 * algorithms
 * Hard (45.25%)
 * Likes:    2176
 * Dislikes: 0
 * Total Accepted:    423.6K
 * Total Submissions: 936.2K
 * Testcase Example:  '[1,2,0]'
 *
 * Given an unsorted integer array nums. Return the smallest positive integer
 * that is not present in nums.
 *
 * You must implement an algorithm that runs in O(n) time and uses O(1)
 * auxiliary space.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,2,0]
 * Output: 3
 * Explanation: The numbers in the range [1,2] are all in the array.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [3,4,-1,1]
 * Output: 2
 * Explanation: 1 is in the array but 2 is missing.
 *
 *
 * Example 3:
 *
 *
 * Input: nums = [7,8,9,11,12]
 * Output: 1
 * Explanation: The smallest positive integer 1 is missing.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^5
 * -2^31 <= nums[i] <= 2^31 - 1
 *
 *
 */

// @lc code=start
int firstMissingPositive(int *nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] > numsSize || nums[i] <= 0)
        {
            nums[i] = -1;
        }
        else if (nums[i] != i + 1)
        {
            int tmp = nums[i], num;
            while (1)
            {
                if (nums[tmp - 1] == tmp)
                {
                    break;
                }
                else if (nums[tmp - 1] > numsSize || nums[tmp - 1] <= 0)
                {
                    nums[tmp - 1] = tmp;
                    break;
                }
                else
                {
                    num = tmp;
                    tmp = nums[tmp - 1];
                    nums[num - 1] = num;
                }
            }
        }
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != i + 1)
        {
            return i + 1;
        }
    }

    return numsSize + 1;
}
// @lc code=end

#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *nums = malloc(sizeof(int) * 4);
    nums[0] = 3;
    nums[1] = 4;
    nums[2] = -1;
    nums[3] = 1;

    int num = firstMissingPositive(nums, 4);
    return 0;
}
