/*
 * @lc app=leetcode.cn id=152 lang=c
 *
 * [152] Maximum Product Subarray
 */

// @lc code=start
#include <stdint.h>
#include <stdlib.h>

int maxProduct(int *nums, int numsSize)
{
    if (numsSize == 1)
    {
        return nums[0];
    }
    int max_product = INT32_MIN, cur_product;

    int start, end, negative_pre_product, negative_next_product, negative_size;
    negative_size = 0, start = 0, end = 0;

    while (1)
    {
        if (end == numsSize)
        {
            if (start == end)
            {
                break;
            }
            else
            {
                if (negative_size == 0 || negative_size % 2 == 0 || end - start == 1)
                {
                    if (max_product < cur_product)
                    {
                        max_product = cur_product;
                    }
                }
                else
                {
                    int removed = cur_product / negative_next_product;
                    if (removed > max_product)
                    {
                        max_product = removed;
                    }
                    removed = cur_product / negative_pre_product;
                    if (removed > max_product)
                    {
                        max_product = removed;
                    }
                }
            }
            break;
        }
        if (nums[end] == 0)
        {
            if (start == end)
            {
                if (max_product < 0)
                {
                    max_product = 0;
                }
            }
            else
            {
                if (negative_size == 0 || negative_size % 2 == 0 || end - start == 1)
                {
                    if (max_product < cur_product)
                    {
                        max_product = cur_product;
                    }
                    if (max_product < 0)
                    {
                        max_product = 0;
                    }
                }
                else
                {
                    int removed = cur_product / negative_next_product;
                    if (removed > max_product)
                    {
                        max_product = removed;
                    }
                    removed = cur_product / negative_pre_product;
                    if (removed > max_product)
                    {
                        max_product = removed;
                    }
                }
            }
            negative_size = 0;
            start = end + 1;
            end = start;
        }
        else
        {
            if (end == start)
            {
                cur_product = nums[end];
            }
            else
            {
                cur_product *= nums[end];
            }

            if (negative_size == 0)
            {
                negative_pre_product = cur_product;
            }

            if (nums[end] > 0 && negative_size > 0)
            {
                negative_next_product *= nums[end];
            }

            if (nums[end] < 0)
            {
                negative_size++;
                negative_next_product = nums[end];
            }
            end++;
        }
    }

    return max_product;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int nums[3] = {-2, 0, -1};
    maxProduct(nums, 3);
    return 0;
}
