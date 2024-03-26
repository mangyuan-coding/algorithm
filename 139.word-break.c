/*
 * @lc app=leetcode.cn id=139 lang=c
 *
 * [139] Word Break
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool wordBreak(char *s, char **wordDict, int wordDictSize)
{
    int len = strlen(s);

    char ***dic = (char ***)malloc(sizeof(char **) * 26);
    int *dic_size = (int *)malloc(sizeof(int) * 26);
    for (int i = 0; i < 26; i++)
    {
        dic_size[i] = 0;
        dic[i] = (char **)malloc(sizeof(char *) * wordDictSize);
    }

    for (int i = 0; i < wordDictSize; i++)
    {
        int idx = wordDict[i][0] - 'a';
        dic_size[idx]++;
        dic[idx][dic_size[idx] - 1] = wordDict[i];
    }

    bool *word_break = (bool *)malloc(sizeof(bool) * len);
    for (int i = 0; i < len; i++)
    {
        word_break[i] = false;
    }

    for (int word_end = 0; word_end < len; word_end++)
    {
        bool can_break = false;
        for (int word_start = word_end; word_start >= 0; word_start--)
        {
            int dic_idx = s[word_start] - 'a';
            if (dic_size[dic_idx] > 0)
            {
                for (int i = 0; i < dic_size[dic_idx]; i++)
                {
                    char *dic_word = dic[dic_idx][i];
                    int word_len = strlen(dic_word);
                    if (word_len == word_end - word_start + 1 && memcmp(s + word_start, dic_word, word_len) == 0 && (word_start == 0 || word_break[word_start - 1]))
                    {
                        can_break = true;
                        break;
                    }
                }
            }
            if (can_break)
            {
                break;
            }
        }
        word_break[word_end] = can_break;
    }
    return word_break[len - 1];
}
// @lc code=end
int main(int argc, char const *argv[])
{
    char **wordDict = (char **)malloc(sizeof(char *) * 5);
    wordDict[0] = "cats";
    wordDict[1] = "dog";
    wordDict[2] = "sand";
    wordDict[3] = "and";
    wordDict[4] = "cat";
    wordBreak("catsandog", wordDict, 5);
    return 0;
}
