/*
 * @lc app=leetcode.cn id=4 lang=c
 *
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (42.08%)
 * Likes:    7190
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 2.7M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return
 * the median of the two sorted arrays.
 *
 * The overall run time complexity should be O(log (m+n)).
 *
 *
 * Example 1:
 *
 *
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.00000
 * Explanation: merged array = [1,2,3] and median is 2.
 *
 *
 * Example 2:
 *
 *
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.50000
 * Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 *
 *
 *
 * Constraints:
 *
 *
 * nums1.length == m
 * nums2.length == n
 * 0 <= m <= 1000
 * 0 <= n <= 1000
 * 1 <= m + n <= 2000
 * -10^6 <= nums1[i], nums2[i] <= 10^6
 *
 *
 */

#include <math.h>
#include <stdbool.h>

// @lc code=start
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{

    if (nums1Size == 0)
    {
        if (nums2Size == 1)
        {
            return nums2[0];
        }
        return nums2Size % 2 == 0 ? ((double)(nums2[nums2Size / 2 - 1] + nums2[nums2Size / 2])) / 2 : nums2[nums2Size / 2];
    }
    if (nums2Size == 0)
    {
        if (nums1Size == 1)
        {
            return nums1[0];
        }
        return nums1Size % 2 == 0 ? ((double)(nums1[nums1Size / 2 - 1] + nums1[nums1Size / 2])) / 2 : nums1[nums1Size / 2];
    }

    int *minor, *major, minor_size, major_size;
    if (nums1Size < nums2Size)
    {
        minor = nums1;
        minor_size = nums1Size;
        major = nums2;
        major_size = nums2Size;
    }
    else
    {
        minor = nums2;
        minor_size = nums2Size;
        major = nums1;
        major_size = nums1Size;
    }

    int size = (minor_size + major_size) / 2;
    bool even = (minor_size + major_size) % 2 == 0;
    int range_l = 0, range_r = minor_size, idx = (range_l + range_r) / 2;
    int from_major = size - idx;

    while (true)
    {
        if (from_major < 0)
        {
            range_r = idx;
            idx = (range_l + range_r) / 2;
            from_major = size - idx;
            continue;
        }
        if (from_major == 0)
        {
            if (minor[idx - 1] <= major[0])
            {
                if (idx == minor_size)
                {
                    return even ? ((double)(minor[idx - 1] + major[0])) / 2 : major[0];
                }
                else
                {
                    return even ? ((double)(minor[idx - 1] + minor[idx])) / 2 : minor[idx];
                }
            }
            if (minor[idx - 1] > major[from_major])
            {
                range_r = idx;
            }
            else
            {
                range_l = idx;
            }
            idx = (range_l + range_r) / 2;
            from_major = size - idx;
            continue;
        }
        int l_max = idx == 0 ? major[from_major - 1] : fmax(minor[idx - 1], major[from_major - 1]);
        int r_min = idx == minor_size ? major[from_major] : from_major == major_size ? minor[idx]
                                                                                     : fmin(minor[idx], major[from_major]);
        if (l_max <= r_min)
        {
            return even ? ((double)(l_max + r_min)) / 2 : r_min;
        }
        else if (idx == 0)
        {
            if (range_l == idx)
            {
                idx = range_r;
                from_major = size - idx;
                continue;
            }
            range_l = idx;
            idx = (range_l + range_r) / 2;
            from_major = size - idx;
            continue;
        }
        else if (from_major == major_size)
        {
            range_r = idx;
            idx = (range_l + range_r) / 2;
            from_major = size - idx;
            continue;
        }
        else if (minor[idx - 1] > major[from_major])
        {
            range_r = idx;
            idx = (range_l + range_r) / 2;
            from_major = size - idx;
            continue;
        }
        else if (range_l == idx)
        {
            idx = range_r;
            from_major = size - idx;
            continue;
        }
        else
        {
            range_l = idx;
            idx = (range_l + range_r) / 2;
            from_major = size - idx;
            continue;
        }
    }
}
// @lc code=end
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *nums1, *nums2, nums1Size, nums2Size;
    nums1Size = 1, nums2Size = 1;
    nums1 = (int *)malloc(sizeof(int) * nums1Size);
    nums2 = (int *)malloc(sizeof(int) * nums2Size);

    nums1[0] = 100001;
    nums2[0] = 100000;

    double median = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);
    printf("median is %f", median);
    return 0;
}
