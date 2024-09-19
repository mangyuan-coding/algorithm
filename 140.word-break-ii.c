/*
 * @lc app=leetcode.cn id=140 lang=c
 *
 * [140] Word Break II
 *
 * https://leetcode.cn/problems/word-break-ii/description/
 *
 * algorithms
 * Hard (59.48%)
 * Likes:    762
 * Dislikes: 0
 * Total Accepted:    103.9K
 * Total Submissions: 174.7K
 * Testcase Example:  '"catsanddog"\n["cat","cats","and","sand","dog"]'
 *
 * Given a string s and a dictionary of strings wordDict, add spaces in s to
 * construct a sentence where each word is a valid dictionary word. Return all
 * such possible sentences in any order.
 *
 * Note that the same word in the dictionary may be reused multiple times in
 * the segmentation.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 *
 *
 * Example 2:
 *
 *
 * Input: s = "pineapplepenapple", wordDict =
 * ["apple","pen","applepen","pine","pineapple"]
 * Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
 * Explanation: Note that you are allowed to reuse a dictionary word.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: []
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 20
 * 1 <= wordDict.length <= 1000
 * 1 <= wordDict[i].length <= 10
 * s and wordDict[i] consist of only lowercase English letters.
 * All the strings of wordDict are unique.
 * Input is generated in a way that the length of the answer doesn't exceed
 * 10^5.
 *
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
const int CHAR_SIZE = 26;

void make_sentences(char *prefix, int prefix_len,
                    char *s, int start, int end,
                    char ***dic, int *dic_size,
                    char **sentences, int *sentence_size)
{
    if (start == end + 1)
    {
        char *sentence = malloc(sizeof(char) * (prefix_len + 1));
        memcpy(sentence, prefix, prefix_len);
        sentence[prefix_len] = '\0';
        sentences[(*sentence_size)++] = sentence;
    }
    else
    {
        int char_idx = s[start] - 'a';
        for (int i = 0; i < dic_size[char_idx]; i++)
        {
            int dic_len = strlen(dic[char_idx][i]);
            if (dic_len > end - start + 1)
            {
                continue;
            }
            if (strncmp(s + start, dic[char_idx][i], dic_len) == 0)
            {
                int next_prefix_len = prefix_len > 0 ? prefix_len + dic_len + 1 : dic_len;
                char *next_prefix = malloc(sizeof(char) * (next_prefix_len + 1));
                if (prefix_len > 0)
                {
                    memcpy(next_prefix, prefix, sizeof(char) * prefix_len);
                    next_prefix[prefix_len] = ' ';
                    memcpy(next_prefix + prefix_len + 1, dic[char_idx][i], sizeof(char) * dic_len);
                }
                else
                {
                    memcpy(next_prefix, dic[char_idx][i], sizeof(char) * dic_len);
                }
                next_prefix[next_prefix_len] = '\0';
                make_sentences(next_prefix, next_prefix_len,
                               s, start + dic_len, end,
                               dic, dic_size,
                               sentences, sentence_size);
            }
        }
    }
}

char **wordBreak(char *s, char **wordDict, int wordDictSize,
                 int *returnSize)
{
    int len = strlen(s);
    char **sentences = calloc(100000, sizeof(char *));
    int *sentence_size = returnSize;
    (*sentence_size) = 0;

    char ***dic = calloc(CHAR_SIZE, sizeof(char **));
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        dic[i] = calloc(wordDictSize, sizeof(char *));
    }

    int *dic_size = calloc(CHAR_SIZE, sizeof(int));
    for (int i = 0; i < wordDictSize; i++)
    {
        int first_char_idx = wordDict[i][0] - 'a';
        dic[first_char_idx][dic_size[first_char_idx]++] = wordDict[i];
    }

    make_sentences(NULL, 0,
                   s, 0, len - 1,
                   dic, dic_size,
                   sentences, sentence_size);

    return sentences;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    char *s = "aaaaaaa";
    int wordDictSize = 3;
    char **wordDict = malloc(sizeof(char *) * wordDictSize);
    wordDict[0] = "aaaa";
    wordDict[1] = "aa";
    wordDict[2] = "a";
    int *returnSize = malloc(sizeof(int));
    char **sentences = wordBreak(s, wordDict, wordDictSize, returnSize);
    printf("[");
    for (int i = 0; i < (*returnSize); i++)
    {
        printf("%s,", sentences[i]);
    }
    printf("]");
    return 0;
}
