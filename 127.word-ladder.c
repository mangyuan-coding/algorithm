/*
 * @lc app=leetcode.cn id=127 lang=c
 *
 * [127] Word Ladder
 *
 * https://leetcode.cn/problems/word-ladder/description/
 *
 * algorithms
 * Hard (49.10%)
 * Likes:    1401
 * Dislikes: 0
 * Total Accepted:    227.5K
 * Total Submissions: 463.4K
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 * A transformation sequence from word beginWord to word endWord using a
 * dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... ->
 * sk such that:
 *
 *
 * Every adjacent pair of words differs by a single letter.
 * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need
 * to be in wordList.
 * sk == endWord
 *
 *
 * Given two words, beginWord and endWord, and a dictionary wordList, return
 * the number of words in the shortest transformation sequence from beginWord
 * to endWord, or 0 if no such sequence exists.
 *
 *
 * Example 1:
 *
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"]
 * Output: 5
 * Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot"
 * -> "dog" -> cog", which is 5 words long.
 *
 *
 * Example 2:
 *
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log"]
 * Output: 0
 * Explanation: The endWord "cog" is not in wordList, therefore there is no
 * valid transformation sequence.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= beginWord.length <= 10
 * endWord.length == beginWord.length
 * 1 <= wordList.length <= 5000
 * wordList[i].length == beginWord.length
 * beginWord, endWord, and wordList[i] consist of lowercase English
 * letters.
 * beginWord != endWord
 * All the words in wordList are unique.
 *
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash/src/uthash.h"

// @lc code=start

const int CHAR_SIZE = 26;

typedef struct IntSet
{
    int val;
    UT_hash_handle hh;
} IntSet;

struct IntSet *find_int(struct IntSet *set, int val)
{
    struct IntSet *_int;
    HASH_FIND_INT(set, &val, _int);
    return _int;
}

bool contains(struct IntSet *set, int val)
{
    return find_int(set, val) != NULL;
}

struct IntSet *add_int(struct IntSet *set, int val)
{
    struct IntSet *_int = find_int(set, val);
    if (_int == NULL)
    {
        _int = malloc(sizeof(struct IntSet));
        _int->val = val;
        HASH_ADD_INT(set, val, _int);
    }
    return set;
}

struct IntSet *remove_int(struct IntSet *set, struct IntSet *_int)
{
    HASH_DEL(set, _int);
    // free(_int);
    return set;
}

struct IntSet *remove_val(struct IntSet *set, int val)
{
    struct IntSet *_int = find_int(set, val);
    if (_int != NULL)
    {
        return remove_int(set, _int);
    }
    return set;
}

struct IntSet *remove_all(struct IntSet *set)
{
    struct IntSet *_int;
    struct IntSet *tmp;
    HASH_ITER(hh, set, _int, tmp)
    {
        HASH_DEL(set, _int);
        // free(_int);
    }
    free(set);
    return NULL;
}

struct IntSet *find_next(struct IntSet *pre_idxes, struct IntSet ***c_pos_idxes,
                         bool *used, int end_word_idx, bool *has_find_end,
                         int word_len, char **words, char *beginWord)
{
    struct IntSet *next_idxes = NULL;
    for (struct IntSet *pre_idx = pre_idxes; pre_idx != NULL;
         pre_idx = (struct IntSet *)(pre_idx->hh.next))
    {
        char *pre = pre_idx->val == -1 ? beginWord : words[pre_idx->val];

        for (int diff_pos = 0; diff_pos < word_len; diff_pos++)
        {
            struct IntSet *next_idx = NULL;
            int pos = 0;
            while (pos < word_len)
            {
                if (pos != diff_pos)
                {
                    int char_idx = pre[pos] - 'a';
                    if (c_pos_idxes[char_idx] == NULL || c_pos_idxes[char_idx][pos] == NULL)
                    {
                        next_idx = remove_all(next_idx);
                        break;
                    }
                    if (next_idx == NULL)
                    {
                        for (struct IntSet *c_pos_idx = c_pos_idxes[char_idx][pos]; c_pos_idx != NULL;
                             c_pos_idx = (struct IntSet *)(c_pos_idx->hh.next))
                        {
                            if (c_pos_idx->val == -1 || !used[c_pos_idx->val])
                            {
                                next_idx = add_int(next_idx, c_pos_idx->val);
                            }
                        }
                        if (next_idx == NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        for (struct IntSet *idx = next_idx; idx != NULL;
                             idx = (struct IntSet *)(idx->hh.next))
                        {
                            if (!contains(c_pos_idxes[char_idx][pos], idx->val))
                            {
                                next_idx = remove_val(next_idx, idx->val);
                            }
                        }
                        if (next_idx == NULL)
                        {
                            break;
                        }
                    }
                }
                if (pos == word_len - 1)
                {
                    int diff_char_idx = pre[diff_pos] - 'a';
                    if (c_pos_idxes[diff_char_idx] != NULL && c_pos_idxes[diff_char_idx][diff_pos] != NULL)
                    {
                        struct IntSet *idx;
                        for (idx = next_idx; idx != NULL;
                             idx = (struct IntSet *)(idx->hh.next))
                        {
                            if (contains(c_pos_idxes[diff_char_idx][diff_pos], idx->val))
                            {
                                next_idx = remove_val(next_idx, idx->val);
                            }
                        }
                    }
                }
                pos++;
            }
            if (next_idx != NULL)
            {
                for (struct IntSet *idx = next_idx; idx != NULL;
                     idx = (struct IntSet *)(idx->hh.next))
                {
                    if (idx->val == end_word_idx)
                    {
                        (*has_find_end) = true;
                    }
                    next_idxes = add_int(next_idxes, idx->val);
                    used[idx->val] = true;
                    for (int i = 0; i < word_len; i++)
                    {
                        int char_idx = words[idx->val][i] - 'a';
                        c_pos_idxes[char_idx][i] = remove_val(c_pos_idxes[char_idx][i], idx->val);
                    }
                }
                next_idx = remove_all(next_idx);
            }
        }
    }

    // free(pre_idxes);
    if ((*has_find_end))
    {
        // free(next_idxes);
        next_idxes = NULL;
    }
    return next_idxes;
}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize)
{
    int word_len = strlen(beginWord);

    int begin_word_idx = -1;
    int end_word_idx = -1;
    for (int idx = 0; idx < wordListSize; idx++)
    {
        if (end_word_idx == -1 && strcmp(wordList[idx], endWord) == 0)
        {
            end_word_idx = idx;
            break;
        }
    }
    if (end_word_idx == -1)
    {
        return 0;
    }
    if (word_len == 1)
    {
        return 2;
    }

    struct IntSet ***begin_c_pos_idxes = calloc(CHAR_SIZE, sizeof(struct IntSet **));
    struct IntSet ***end_c_pos_idxes = calloc(CHAR_SIZE, sizeof(struct IntSet **));
    for (int idx = 0; idx < wordListSize; idx++)
    {
        if (strcmp(beginWord, wordList[idx]) == 0)
        {
            begin_word_idx = idx;
        }
        for (int pos = 0; pos < word_len; pos++)
        {
            int char_idx = wordList[idx][pos] - 'a';
            if (begin_c_pos_idxes[char_idx] == NULL)
            {
                begin_c_pos_idxes[char_idx] = calloc(word_len, sizeof(struct IntSet *));
            }
            begin_c_pos_idxes[char_idx][pos] = add_int(begin_c_pos_idxes[char_idx][pos], idx);
            if (end_c_pos_idxes[char_idx] == NULL)
            {
                end_c_pos_idxes[char_idx] = calloc(word_len, sizeof(struct IntSet *));
            }
            end_c_pos_idxes[char_idx][pos] = add_int(end_c_pos_idxes[char_idx][pos], idx);
        }
    }

    struct IntSet *begin_idxes = NULL;
    begin_idxes = add_int(begin_idxes, begin_word_idx);
    bool *begin_used = calloc(wordListSize, sizeof(bool));
    if (begin_word_idx != -1)
    {
        begin_used[begin_word_idx] = true;
    }
    int begin_deep = 0;
    bool *begin_has_find_end = calloc(1, sizeof(bool));

    struct IntSet *end_idxes = NULL;
    end_idxes = add_int(end_idxes, end_word_idx);
    bool *end_used = calloc(wordListSize, sizeof(bool));
    end_used[end_word_idx] = true;
    int end_deep = 0;
    bool *end_has_find_begin = calloc(1, sizeof(bool));

    while (begin_idxes != NULL && HASH_COUNT(begin_idxes) > 0 &&
           (end_idxes != NULL && HASH_COUNT(end_idxes) > 0))
    {
        for (struct IntSet *idx = begin_idxes; idx != NULL;
             idx = (struct IntSet *)(idx->hh.next))
        {
            if (idx->val != -1 && end_used[idx->val])
            {
                return begin_deep + end_deep + 1;
            }
        }
        begin_deep++;
        begin_idxes = find_next(begin_idxes, begin_c_pos_idxes,
                                begin_used, end_word_idx, begin_has_find_end,
                                word_len, wordList, beginWord);

        for (struct IntSet *idx = end_idxes; idx != NULL;
             idx = (struct IntSet *)(idx->hh.next))
        {
            if (idx->val != -1 && begin_used[idx->val])
            {
                return begin_deep + end_deep + 1;
            }
        }
        end_deep++;
        end_idxes = find_next(end_idxes, end_c_pos_idxes,
                              end_used, begin_word_idx, end_has_find_begin,
                              word_len, wordList, beginWord);
    }

    if ((*begin_has_find_end))
    {
        return begin_deep + 1;
    }
    else if ((*end_has_find_begin))
    {
        return end_deep + 1;
    }

    return 0;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    char *beginWord = "hit", *endWord = "cog";
    int wordListSize = 6;
    char **wordList = malloc(sizeof(char *) * wordListSize);
    wordList[0] = "hot";
    wordList[1] = "dot";
    wordList[2] = "dog";
    wordList[3] = "lot";
    wordList[4] = "log";
    wordList[5] = "cog";
    int len = ladderLength(beginWord, endWord, wordList, wordListSize);
    return 0;
}
