/*
 * @lc app=leetcode.cn id=76 lang=c
 *
 * [76] Minimum Window Substring
 *
 * https://leetcode.cn/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (46.14%)
 * Likes:    2971
 * Dislikes: 0
 * Total Accepted:    621.9K
 * Total Submissions: 1.3M
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * Given two strings s and t of lengths m and n respectively, return the
 * minimum window substring of s such that every character in t (including
 * duplicates) is included in the window. If there is no such substring, return
 * the empty string "".
 *
 * The testcases will be generated such that the answer is unique.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation: The entire string s is the minimum window.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 *
 *
 *
 * Constraints:
 *
 *
 * m == s.length
 * n == t.length
 * 1 <= m, n <= 10^5
 * s and t consist of uppercase and lowercase English letters.
 *
 *
 *
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 *
 */

// @lc code=start

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *minWindow(char *s, char *t)
{
    int s_len = strlen(s), t_len = strlen(t);
    if (s_len < t_len)
    {
        return "";
    }
    if (t_len == 1)
    {
        for (int i = 0; i < s_len; i++)
        {
            if (s[i] == t[0])
            {
                return t;
            }
        }
        return "";
    }
    // 65-90: 'A'-'Z'; 97-122: 'a'-'z'
    int *remain_chars = calloc(58, sizeof(int));
    bool *type_chars = malloc(sizeof(bool) * 58);
    for (int i = 0; i < 58; i++)
    {
        type_chars[i] = false;
    }
    int remain_char_size = 0;
    for (int i = 0; i < t_len; i++)
    {
        remain_chars[t[i] - 'A']++;
        type_chars[t[i] - 'A'] = true;
        remain_char_size++;
    }
    int cur = 0, min_start = -1, min_end = s_len - 1;
    int *include = malloc(sizeof(int) * s_len);
    int include_size = 0, include_idx = 0;
    while (1)
    {
        char cur_char = s[cur];
        int cur_char_idx = cur_char - 'A';
        if (type_chars[cur_char_idx])
        {
            include[include_size++] = cur;
            if (remain_chars[cur_char_idx] > 0)
            {

                remain_chars[cur_char_idx]--;
                remain_char_size--;
                if (remain_char_size == 0)
                {
                    if (min_start == -1 ||
                        min_end - min_start > cur - include[include_idx])
                    {
                        min_start = include[include_idx];
                        min_end = cur;
                    }
                    char exclude = s[include[include_idx++]];
                    int exclude_char_idx = exclude - 'A';
                    remain_chars[exclude_char_idx]++;
                    remain_char_size++;
                }
            }
            else
            {
                int first_exist_idx;
                for (int i = include_idx; i < include_size; i++)
                {
                    if (s[include[i]] == cur_char)
                    {
                        first_exist_idx = i;
                        break;
                    }
                }
                for (int i = first_exist_idx; i > include_idx; i--)
                {
                    include[i] = include[i - 1];
                }
                include_idx++;
            }
        }
        cur++;
        if (cur == s_len)
        {
            break;
        }
    }
    if (min_start == -1)
    {
        return "";
    }
    else
    {
        char *window = malloc(sizeof(char) * (min_end - min_start + 2));
        memcpy(window, s + min_start, sizeof(char) * (min_end - min_start + 1));
        window[min_end - min_start + 1] = '\0';
        return window;
    }
}
// @lc code=end
#include <stdio.h>

char *build_dy_chars(char *origin, int size)
{
    char *builded = malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size; i++)
    {
        builded[i] = origin[i];
    }
    builded[size] = '\0';
    return builded;
}

int main(int argc, char const *argv[])
{
    printf("window %s", minWindow(build_dy_chars("cgklivwehljxrdzpfdqsapogwvjtvbzahjnsejwnuhmomlfsrvmrnczjzjevkdvroiluthhpqtffhlzyglrvorgnalk", 92), "mqfff"));
    return 0;
}
