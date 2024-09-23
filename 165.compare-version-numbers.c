/*
 * @lc app=leetcode.cn id=165 lang=c
 *
 * [165] Compare Version Numbers
 *
 * https://leetcode.cn/problems/compare-version-numbers/description/
 *
 * algorithms
 * Medium (52.80%)
 * Likes:    433
 * Dislikes: 0
 * Total Accepted:    187.6K
 * Total Submissions: 355.4K
 * Testcase Example:  '"1.2"\n"1.10"'
 *
 * Given two version strings, version1 and version2, compare them. A version
 * string consists of revisions separated by dots '.'. The value of the
 * revision is its integer conversion ignoring leading zeros.
 *
 * To compare version strings, compare their revision values in left-to-right
 * order. If one of the version strings has fewer revisions, treat the missing
 * revision values as 0.
 *
 * Return the following:
 *
 *
 * If version1 < version2, return -1.
 * If version1 > version2, return 1.
 * Otherwise, return 0.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: version1 = "1.2", version2 = "1.10"
 *
 * Output: -1
 *
 * Explanation:
 *
 * version1's second revision is "2" and version2's second revision is "10": 2
 * < 10, so version1 < version2.
 *
 *
 * Example 2:
 *
 *
 * Input: version1 = "1.01", version2 = "1.001"
 *
 * Output: 0
 *
 * Explanation:
 *
 * Ignoring leading zeroes, both "01" and "001" represent the same integer
 * "1".
 *
 *
 * Example 3:
 *
 *
 * Input: version1 = "1.0", version2 = "1.0.0.0"
 *
 * Output: 0
 *
 * Explanation:
 *
 * version1 has less revisions, which means every missing revision are treated
 * as "0".
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= version1.length, version2.length <= 500
 * version1 and version2 only contain digits and '.'.
 * version1 and version2 are valid version numbers.
 * All the given revisions in version1 and version2 can be stored in a 32-bit
 * integer.
 *
 *
 */

#include <string.h>

// @lc code=start
int compareVersion(char *version1, char *version2)
{
    int v_1_len = strlen(version1), v_2_len = strlen(version2);
    int start_1 = 0, end_1 = 0, start_2 = 0, end_2 = 0;
    while (1)
    {
        if (end_1 == v_1_len && end_2 == v_2_len)
        {
            if (start_1 == end_1 && start_2 == end_2)
            {
                return 0;
            }
            else if (start_1 == end_1)
            {
                return -1;
            }
            else if (start_2 == end_2)
            {
                return 1;
            }
            else
            {
                if (end_2 - start_2 > end_1 - start_1)
                {
                    return -1;
                }
                else if (end_2 - start_2 < end_1 - start_1)
                {
                    return 1;
                }
                else
                {
                    while (1)
                    {
                        if (start_1 == end_1)
                        {
                            break;
                        }
                        if (version1[start_1] > version2[start_2])
                        {
                            return 1;
                        }
                        else if (version1[start_1] < version2[start_2])
                        {
                            return -1;
                        }
                        else
                        {
                            start_1++;
                            start_2++;
                        }
                    }
                    end_1++;
                    start_1 = end_1;
                    end_2++;
                    start_2 = end_2;
                }
            }
            break;
        }
        else if (end_1 == v_1_len)
        {
            if (version2[end_2] == '.')
            {
                if (end_2 - start_2 > end_1 - start_1)
                {
                    return -1;
                }
                else if (end_2 - start_2 < end_1 - start_1)
                {
                    return 1;
                }
                else
                {
                    while (1)
                    {
                        if (start_1 == end_1)
                        {
                            break;
                        }
                        if (version1[start_1] > version2[start_2])
                        {
                            return 1;
                        }
                        else if (version1[start_1] < version2[start_2])
                        {
                            return -1;
                        }
                        else
                        {
                            start_1++;
                            start_2++;
                        }
                    }
                    end_2++;
                    start_2 = end_2;
                }
            }
            else
            {
                if (version2[end_2] == '0' && start_2 == end_2)
                {
                    start_2++;
                }
                end_2++;
            }
        }
        else if (end_2 == v_2_len)
        {
            if (version1[end_1] == '.')
            {
                if (end_2 - start_2 > end_1 - start_1)
                {
                    return -1;
                }
                else if (end_2 - start_2 < end_1 - start_1)
                {
                    return 1;
                }
                else
                {
                    while (1)
                    {
                        if (start_1 == end_1)
                        {
                            break;
                        }
                        if (version1[start_1] > version2[start_2])
                        {
                            return 1;
                        }
                        else if (version1[start_1] < version2[start_2])
                        {
                            return -1;
                        }
                        else
                        {
                            start_1++;
                            start_2++;
                        }
                    }
                    end_1++;
                    start_1 = end_1;
                }
            }
            else
            {
                if (version1[end_1] == '0' && start_1 == end_1)
                {
                    start_1++;
                }
                end_1++;
            }
        }
        else
        {
            if (version1[end_1] == '.' && version2[end_2] == '.')
            {
                if (start_1 == end_1 && start_2 == end_2)
                {
                    end_1++;
                    start_1 = end_1;
                    end_2++;
                    start_2 = end_2;
                }
                else if (start_1 == end_1)
                {
                    return -1;
                }
                else if (start_2 == end_2)
                {
                    return 1;
                }
                else
                {
                    if (end_2 - start_2 > end_1 - start_1)
                    {
                        return -1;
                    }
                    else if (end_2 - start_2 < end_1 - start_1)
                    {
                        return 1;
                    }
                    else
                    {
                        while (1)
                        {
                            if (start_1 == end_1)
                            {
                                break;
                            }
                            if (version1[start_1] > version2[start_2])
                            {
                                return 1;
                            }
                            else if (version1[start_1] < version2[start_2])
                            {
                                return -1;
                            }
                            else
                            {
                                start_1++;
                                start_2++;
                            }
                        }
                        end_1++;
                        start_1 = end_1;
                        end_2++;
                        start_2 = end_2;
                    }
                }
            }
            else if (version1[end_1] == '.')
            {
                if (version2[end_2] == '0' && start_2 == end_2)
                {
                    start_2++;
                }
                end_2++;
            }
            else if (version2[end_2] == '.')
            {
                if (version1[end_1] == '0' && start_1 == end_1)
                {
                    start_1++;
                }
                end_1++;
            }
            else
            {
                if (version1[end_1] == '0' && start_1 == end_1)
                {
                    start_1++;
                }
                end_1++;
                if (version2[end_2] == '0' && start_2 == end_2)
                {
                    start_2++;
                }
                end_2++;
            }
        }
    }

    return 0;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int compared = compareVersion("1.0", "1.0.0.0");
    return 0;
}
