/*
 * @lc app=leetcode id=136 lang=c
 *
 * [136] Single Number
 */

// @lc code=start
#include <stdlib.h>

// int int_cmp(const void *a, const void *b)
// {
//     return (*(int *)a - *(int *)b);
// }

// int singleNumber(int *nums, int numsSize)
// {
//     if (numsSize == 1)
//     {
//         return nums[0];
//     }

//     qsort(nums, numsSize, sizeof(int), int_cmp);

//     if (nums[0] != nums[1])
//     {
//         return nums[0];
//     }
//     if (nums[numsSize - 1] != nums[numsSize - 2])
//     {
//         return nums[numsSize - 1];
//     }

//     int left = 0, right = numsSize - 1, half;
//     while (left < right)
//     {
//         half = (left + right) / 2;
//         if (nums[half] == nums[half - 1])
//         {
//             if ((half - 1 - left) % 2 == 0)
//             {
//                 left = half + 1;
//             }
//             else
//             {
//                 right = half - 2;
//             }
//         }
//         else if (nums[half] == nums[half + 1])
//         {
//             if ((half - left) % 2 == 0)
//             {
//                 left = half + 2;
//             }
//             else
//             {
//                 right = half - 1;
//             }
//         }
//         else
//         {
//             return nums[half];
//         }
//     }

//     return nums[left];
// }

int singleNumber(int *nums, int numsSize)
{
    int ret = nums[00];
    for (int i = 1; i < numsSize; i++)
    {
        ret ^= nums[i];
    }
    return ret;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int nums[49] = {-967, -590, 980, -806, 145, -881, 357, -787, -592, 859, 627, -929, 296, 818, -194, 586, -106, -479, 967, 132, -396, -692, 464, 726, -967, -590, 980, -806, 145, -881, 357, -787, -592, 859, 627, -929, 296, 818, -194, 586, -106, -479, 967, 132, -396, -692, 464, 726, -755};
    singleNumber(nums, 49);
    return 0;
}
