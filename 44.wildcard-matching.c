/*
 * @lc app=leetcode.cn id=44 lang=c
 *
 * [44] Wildcard Matching
 *
 * https://leetcode.cn/problems/wildcard-matching/description/
 *
 * algorithms
 * Hard (34.06%)
 * Likes:    1156
 * Dislikes: 0
 * Total Accepted:    160.8K
 * Total Submissions: 472.1K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*' where:
 *
 *
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 *
 *
 * The matching should cover the entire input string (not partial).
 *
 *
 * Example 1:
 *
 *
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 *
 *
 * Example 2:
 *
 *
 * Input: s = "aa", p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "cb", p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not
 * match 'b'.
 *
 *
 *
 * Constraints:
 *
 *
 * 0 <= s.length, p.length <= 2000
 * s contains only lowercase English letters.
 * p contains only lowercase English letters, '?' or '*'.
 *
 *
 */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// @lc code=start

typedef struct sub_pattern
{
    bool any_chars;
    char *pattern;
    int pattern_size;
} sub_pattern;

bool is_match(char *s, int start, int s_len, struct sub_pattern **sub_ps, int sub_ps_idx, int sub_ps_len,
              int **records)
{
    if (sub_ps_idx == sub_ps_len)
    {
        return start == s_len;
    }
    if (start == s_len)
    {
        for (int i = sub_ps_idx; i < sub_ps_len; i++)
        {
            if (!sub_ps[i]->any_chars)
            {
                return false;
            }
        }
        return true;
    }
    if (records[start][sub_ps_idx] != -1)
    {
        return records[start][sub_ps_idx] == 1;
    }
    int s_idx;
    struct sub_pattern *sub_p = sub_ps[sub_ps_idx];
    if (!sub_p->any_chars)
    {
        s_idx = start;
        for (int i = 0; i < sub_p->pattern_size; i++)
        {
            if (s_idx == s_len)
            {
                records[start][sub_ps_idx] = 0;
                return false;
            }
            if (sub_p->pattern[i] != s[s_idx] && sub_p->pattern[i] != '?')
            {
                records[start][sub_ps_idx] = 0;
                return false;
            }
            s_idx++;
        }
        return is_match(s, s_idx, s_len, sub_ps, sub_ps_idx + 1, sub_ps_len, records);
    }
    else
    {
        s_idx = start;
        while (s_idx <= s_len)
        {
            if (is_match(s, s_idx, s_len, sub_ps, sub_ps_idx + 1, sub_ps_len, records))
            {
                records[start][sub_ps_idx] = 1;
                return true;
            }
            else
            {
                s_idx++;
            }
        }
        records[start][sub_ps_idx] = 0;
        return false;
    }
}

bool isMatch(char *s, char *p)
{
    int p_len = strlen(p);

    struct sub_pattern **sub_p = (struct sub_pattern **)malloc(sizeof(struct sub_pattern *) * p_len);
    int sub_p_len = 0;
    int idx_p = 0, idx_p_next = 0;
    while (1)
    {
        if (idx_p_next == p_len)
        {
            if (idx_p_next == idx_p)
            {
                break;
            }
            sub_p[sub_p_len++] = (struct sub_pattern *)malloc(sizeof(struct sub_pattern));
            sub_p[sub_p_len - 1]->any_chars = false;
            sub_p[sub_p_len - 1]->pattern_size = idx_p_next - idx_p;
            sub_p[sub_p_len - 1]->pattern = (char *)malloc(sizeof(char) * (sub_p[sub_p_len - 1]->pattern_size + 1));
            memcpy(sub_p[sub_p_len - 1]->pattern, p + idx_p, sizeof(char) * sub_p[sub_p_len - 1]->pattern_size);
            sub_p[sub_p_len - 1]->pattern[sub_p[sub_p_len - 1]->pattern_size] = '\0';
            break;
        }
        if (p[idx_p_next] != '*')
        {
            idx_p_next++;
        }
        else
        {
            if (idx_p_next > idx_p)
            {
                sub_p[sub_p_len++] = (struct sub_pattern *)malloc(sizeof(struct sub_pattern));
                sub_p[sub_p_len - 1]->any_chars = false;
                sub_p[sub_p_len - 1]->pattern_size = idx_p_next - idx_p;
                sub_p[sub_p_len - 1]->pattern = (char *)malloc(sizeof(char) * (sub_p[sub_p_len - 1]->pattern_size + 1));
                memcpy(sub_p[sub_p_len - 1]->pattern, p + idx_p, sizeof(char) * sub_p[sub_p_len - 1]->pattern_size);
                sub_p[sub_p_len - 1]->pattern[sub_p[sub_p_len - 1]->pattern_size] = '\0';
            }

            sub_p[sub_p_len++] = (struct sub_pattern *)malloc(sizeof(struct sub_pattern));
            sub_p[sub_p_len - 1]->any_chars = true;
            idx_p_next++;
            idx_p = idx_p_next;
        }
    }
    int s_len = strlen(s);
    int **records = (int **)malloc(sizeof(int *) * s_len);
    for (int i = 0; i < s_len; i++)
    {
        records[i] = (int *)malloc(sizeof(int) * sub_p_len);
        for (int j = 0; j < sub_p_len; j++)
        {
            records[i][j] = -1;
        }
    }

    return is_match(s, 0, s_len, sub_p, 0, sub_p_len, records);
}
// @lc code=end
int main(int argc, char const *argv[])
{
    printf("is marched %d", isMatch("aab", "c*a*b"));
    return 0;
}
