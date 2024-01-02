/*
 * @lc app=leetcode id=88 lang=c
 *
 * [88] Merge Sorted Array
 */

// @lc code=start
void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    if (n == 0)
    {
        return;
    }
    if (m == 0)
    {
        for (int i = 0; i < n; i++)
        {
            nums1[i] = nums2[i];
        }
        return;
    }

    int idx_1 = m - 1, idx_2 = n - 1, idx = m + n - 1;
    while (idx >= 0)
    {
        if (idx_2 < 0)
        {
            nums1[idx--] = nums1[idx_1--];
        }
        else if (idx_1 < 0)
        {
            nums1[idx--] = nums2[idx_2--];
        }
        else if (nums1[idx_1] < nums2[idx_2])
        {
            nums1[idx--] = nums2[idx_2--];
        }
        else
        {
            nums1[idx--] = nums1[idx_1--];
        }
    }
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int nums1[6] = {4, 0, 0, 0, 0, 0};
    int nums2[5] = {1, 2, 3, 5, 6};
    merge(nums1, 6, 1, nums2, 5, 5);
    for (int i = 0; i < 6; i++)
    {
        printf("%d,", nums1[i]);
    }

    /* code */
    return 0;
}
