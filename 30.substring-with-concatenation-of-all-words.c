/*
 * @lc app=leetcode.cn id=30 lang=c
 *
 * [30] Substring with Concatenation of All Words
 *
 * https://leetcode.cn/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (38.66%)
 * Likes:    1137
 * Dislikes: 0
 * Total Accepted:    217K
 * Total Submissions: 561.4K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 * You are given a string s and an array of strings words. All the strings of
 * words are of the same length.
 *
 * A concatenated string is a string that exactly contains all the strings of
 * any permutation of words concatenated.
 *
 *
 * For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef",
 * "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is
 * not a concatenated string because it is not the concatenation of any
 * permutation of words.
 *
 *
 * Return an array of the starting indices of all the concatenated substrings
 * in s. You can return the answer in any order.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "barfoothefoobarman", words = ["foo","bar"]
 *
 * Output: [0,9]
 *
 * Explanation:
 *
 * The substring starting at 0 is "barfoo". It is the concatenation of
 * ["bar","foo"] which is a permutation of words.
 * The substring starting at 9 is "foobar". It is the concatenation of
 * ["foo","bar"] which is a permutation of words.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "wordgoodgoodgoodbestword", words =
 * ["word","good","best","word"]
 *
 * Output: []
 *
 * Explanation:
 *
 * There is no concatenated substring.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
 *
 * Output: [6,9,12]
 *
 * Explanation:
 *
 * The substring starting at 6 is "foobarthe". It is the concatenation of
 * ["foo","bar","the"].
 * The substring starting at 9 is "barthefoo". It is the concatenation of
 * ["bar","the","foo"].
 * The substring starting at 12 is "thefoobar". It is the concatenation of
 * ["the","foo","bar"].
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^4
 * 1 <= words.length <= 5000
 * 1 <= words[i].length <= 30
 * s and words[i] consist of lowercase English letters.
 *
 *
 */

#include <string.h>

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

bool matched(char *s, int start, int s_len,
             int **each_idx_matched_words_idx, int *each_idx_matched_words_size,
             int *each_unique_words_size, int unique_words_len, int word_len,
             int *each_word_used_size, int used_size, int words_size)
{
    if (used_size == words_size)
    {
        return true;
    }
    if (each_idx_matched_words_idx[start] == NULL)
    {
        return false;
    }
    for (int i = 0; i < each_idx_matched_words_size[start]; i++)
    {
        int used_unique_word_idx = each_idx_matched_words_idx[start][i];
        if (each_word_used_size[used_unique_word_idx] < each_unique_words_size[used_unique_word_idx])
        {
            each_word_used_size[used_unique_word_idx]++;
            if (matched(s, start + word_len, s_len,
                        each_idx_matched_words_idx, each_idx_matched_words_size,
                        each_unique_words_size, unique_words_len, word_len,
                        each_word_used_size, used_size + 1, words_size))
            {
                each_word_used_size[used_unique_word_idx]--;
                return true;
            }
            else
            {
                each_word_used_size[used_unique_word_idx]--;
            }
        }
    }
    return false;
}

int *findSubstring(char *s, char **words, int wordsSize, int *returnSize)
{
    int word_len = strlen(words[0]);
    int s_len = strlen(s);
    int words_len = word_len * wordsSize;
    if (s_len < words_len)
    {
        *returnSize = 0;
        return NULL;
    }

    char **unique_words = (char **)malloc(sizeof(char *) * s_len);
    int unique_words_len = 0;
    int *each_unique_words_size = (int *)malloc(sizeof(int) * s_len);
    bool contains = false;
    for (int i = 0; i < wordsSize; i++)
    {
        if (i == 0)
        {
            unique_words[unique_words_len++] = words[i];
            each_unique_words_size[unique_words_len - 1] = 1;
        }
        if (i != 0)
        {
            contains = false;
            for (int j = 0; j < unique_words_len; j++)
            {
                if (strcmp(words[i], unique_words[j]) == 0)
                {
                    contains = true;
                    each_unique_words_size[j]++;
                    break;
                }
            }
            if (!contains)
            {
                unique_words[unique_words_len++] = words[i];
                each_unique_words_size[unique_words_len - 1] = 1;
            }
        }
    }

    int **each_idx_matched_words_idx = (int **)malloc(sizeof(int *) * s_len);
    int *each_idx_matched_words_size = (int *)malloc(sizeof(int) * s_len);
    for (int i = 0; i < s_len; i++)
    {
        each_idx_matched_words_idx[i] = NULL;
        for (int j = 0; j < unique_words_len; j++)
        {
            if (strncmp(s + i, unique_words[j], word_len) == 0)
            {
                if (each_idx_matched_words_idx[i] == NULL)
                {
                    each_idx_matched_words_idx[i] = (int *)malloc(sizeof(int) * unique_words_len);
                    each_idx_matched_words_size[i] = 1;
                    each_idx_matched_words_idx[i][each_idx_matched_words_size[i] - 1] = j;
                }
                else
                {
                    each_idx_matched_words_size[i]++;
                    each_idx_matched_words_idx[i][each_idx_matched_words_size[i] - 1] = j;
                }
            }
        }
    }

    int *matched_idxes = (int *)malloc(sizeof(int) * s_len);
    *returnSize = 0;
    int *each_word_used_size = (int *)malloc(sizeof(int) * unique_words_len);
    int used_size = 0;
    for (int i = 0; i < unique_words_len; i++)
    {
        each_word_used_size[i] = 0;
    }

    for (int i = 0; i < s_len; i++)
    {
        if (s_len - i < words_len)
        {
            break;
        }
        if (matched(s, i, s_len, each_idx_matched_words_idx, each_idx_matched_words_size,
                    each_unique_words_size, unique_words_len, word_len, each_word_used_size,
                    used_size, wordsSize))
        {
            matched_idxes[(*returnSize)++] = i;
        }
    }
    return matched_idxes;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *s = "barfoothefoobarman";
    char **words = (char **)malloc(sizeof(char *) * 2);
    words[0] = "foo";
    words[1] = "bar";
    int *returnSize = (int *)malloc(sizeof(int));
    int *idxes = findSubstring(s, words, 2, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%d,", idxes[i]);
    }
    return 0;
}
