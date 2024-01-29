/*
 * @lc app=leetcode id=80 lang=c
 *
 * [80] Remove Duplicates from Sorted Array II
 */

// @lc code=start
int removeDuplicates(int *nums, int numsSize)
{

    if (numsSize <= 2)
    {
        return numsSize;
    }

    int pre_num_end = -1, cur_num_start = 0, cur_num_counter = 1;
    while (cur_num_start + cur_num_counter <= numsSize)
    {
        if (cur_num_start == numsSize - 1)
        {
            nums[++pre_num_end] = nums[cur_num_start];
            break;
        }
        else if (cur_num_start + cur_num_counter == numsSize)
        {
            nums[++pre_num_end] = nums[cur_num_start];
            if (cur_num_counter > 1)
            {
                nums[++pre_num_end] = nums[cur_num_start + 1];
            }
            break;
        }
        else if (nums[cur_num_start + cur_num_counter] != nums[cur_num_start])
        {
            nums[++pre_num_end] = nums[cur_num_start];
            if (cur_num_counter > 1)
            {
                nums[++pre_num_end] = nums[cur_num_start + 1];
            }
            cur_num_start += cur_num_counter;
            cur_num_counter = 1;
        }
        else
        {
            cur_num_counter++;
        }
    }

    return pre_num_end + 1;
}
// @lc code=end
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *nums = (int *)malloc(sizeof(int) * 6);
    nums[0] = 1;
    nums[1] = 1;
    nums[2] = 1;
    nums[3] = 2;
    nums[4] = 2;
    nums[5] = 3;
    int k = removeDuplicates(nums, 6);
    return 0;
}
