#
# @lc app=leetcode.cn id=4 lang=python3
#
# [4] 寻找两个正序数组的中位数
#
# https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
#
# algorithms
# Hard (41.52%)
# Likes:    6631
# Dislikes: 0
# Total Accepted:    972.8K
# Total Submissions: 2.3M
# Testcase Example:  '[1,3]\n[2]'
#
# 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
# 
# 算法的时间复杂度应该为 O(log (m+n)) 。
# 
# 
# 
# 示例 1：
# 
# 
# 输入：nums1 = [1,3], nums2 = [2]
# 输出：2.00000
# 解释：合并数组 = [1,2,3] ，中位数 2
# 
# 
# 示例 2：
# 
# 
# 输入：nums1 = [1,2], nums2 = [3,4]
# 输出：2.50000
# 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
# 
# 
# 
# 
# 
# 
# 提示：
# 
# 
# nums1.length == m
# nums2.length == n
# 0 <= m <= 1000
# 0 <= n <= 1000
# 1 <= m + n <= 2000
# -10^6 <= nums1[i], nums2[i] <= 10^6
# 
# 
#

# @lc code=start
class Solution:
    def findSingleSortedArrays(self, nums: List[int]) -> float:
        n = len(nums)
        if n == 1:
            return nums[0]
        elif n % 2 == 0:
            return (nums[n // 2 - 1] + nums[n // 2]) / 2
        else:
            return nums[n // 2]
        
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        n1 = len(nums1); n2 = len(nums2)

        if n1 == 0: return self.findSingleSortedArrays(nums2)
        if n2 == 0: return self.findSingleSortedArrays(nums1)

        if n1 == 1 and n2 == 1: return (nums1[0] + nums2[0]) / 2;

        maxNums = nums1 if nums1[n1 - 1] > nums2[n2 - 1] else nums2
        minNums = nums1 if nums1[0] < nums2[0] else nums2
        
        if (maxNums is minNums) & (len(maxNums) == 2): 
            return self.findSingleSortedArrays(nums1 if maxNums is nums2 else nums2);

        splitNums1 = nums1
        splitNums2 = nums2

        if maxNums is nums1:
            splitNums1 = splitNums1[:-1:]
        else:
            splitNums2 = splitNums2[:-1:]
        if minNums is nums1:
            splitNums1 = splitNums1[1:]
        else:
            splitNums2 = splitNums2[1:]

        return self.findMedianSortedArrays(splitNums1, splitNums2)