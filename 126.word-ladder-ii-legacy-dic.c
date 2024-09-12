/*
 * @lc app=leetcode.cn id=126 lang=c
 *
 * [126] Word Ladder II
 *
 * https://leetcode.cn/problems/word-ladder-ii/description/
 *
 * algorithms
 * Hard (36.71%)
 * Likes:    724
 * Dislikes: 0
 * Total Accepted:    60.9K
 * Total Submissions: 165.8K
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
 * all the shortest transformation sequences from beginWord to endWord, or an
 * empty list if no such sequence exists. Each sequence should be returned as a
 * list of the words [beginWord, s1, s2, ..., sk].
 *
 *
 * Example 1:
 *
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"]
 * Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
 * Explanation: There are 2 shortest transformation sequences:
 * "hit" -> "hot" -> "dot" -> "dog" -> "cog"
 * "hit" -> "hot" -> "lot" -> "log" -> "cog"
 *
 *
 * Example 2:
 *
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log"]
 * Output: []
 * Explanation: The endWord "cog" is not in wordList, therefore there is no
 * valid transformation sequence.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= beginWord.length <= 5
 * endWord.length == beginWord.length
 * 1 <= wordList.length <= 500
 * wordList[i].length == beginWord.length
 * beginWord, endWord, and wordList[i] consist of lowercase English
 * letters.
 * beginWord != endWord
 * All the words in wordList are unique.
 * The sum of all shortest transformation sequences does not exceed 10^5.
 *
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash/src/uthash.h"

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

const int CHAR_SIZE = 26;

typedef struct WordTreeNode
{
    int word_idx;
    char *word;
    int children_size;
    struct WordTreeNode **children;
    int parent_size;
    struct WordTreeNode **parents;
} WordTreeNode;

typedef struct Ladder
{
    int word_size;
    char **words;
} Ladder;

typedef struct Ladders
{
    int ladder_size;
    struct Ladder **ladders;
} Ladders;

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

struct WordTreeNode **build_children(struct WordTreeNode **nodes, int *node_size,
                                     struct IntSet ***c_pos_idxes,
                                     bool *used, int end_word_idx, bool *has_find_end,
                                     int word_len,
                                     char **words, struct WordTreeNode **idx_nodes)
{
    struct IntSet *child_idxes = NULL;
    for (int i = 0; i < (*node_size); i++)
    {
        for (int diff_pos = 0; diff_pos < word_len; diff_pos++)
        {
            struct IntSet *r_child_idxes = NULL;
            int pos = 0;
            while (pos < word_len)
            {
                if (pos != diff_pos)
                {
                    int char_idx = nodes[i]->word[pos] - 'a';
                    if (c_pos_idxes[char_idx] == NULL || c_pos_idxes[char_idx][pos] == NULL)
                    {
                        r_child_idxes = remove_all(r_child_idxes);
                        break;
                    }
                    if (r_child_idxes == NULL)
                    {
                        struct IntSet *c_pos_idx;

                        for (c_pos_idx = c_pos_idxes[char_idx][pos]; c_pos_idx != NULL;
                             c_pos_idx = (struct IntSet *)(c_pos_idx->hh.next))
                        {
                            if (!used[c_pos_idx->val])
                            {
                                r_child_idxes = add_int(r_child_idxes, c_pos_idx->val);
                            }
                        }
                        if (r_child_idxes == NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        struct IntSet *r_child_idx;
                        for (r_child_idx = r_child_idxes; r_child_idx != NULL;
                             r_child_idx = (struct IntSet *)(r_child_idx->hh.next))
                        {
                            if (!contains(c_pos_idxes[char_idx][pos], r_child_idx->val))
                            {
                                r_child_idxes = remove_val(r_child_idxes, r_child_idx->val);
                            }
                        }
                        if (r_child_idxes == NULL)
                        {
                            break;
                        }
                    }
                }
                if (pos == word_len - 1)
                {
                    int diff_char_idx = nodes[i]->word[diff_pos] - 'a';
                    if (c_pos_idxes[diff_char_idx] != NULL && c_pos_idxes[diff_char_idx][diff_pos] != NULL)
                    {
                        struct IntSet *r_child_idx;
                        for (r_child_idx = r_child_idxes; r_child_idx != NULL;
                             r_child_idx = (struct IntSet *)(r_child_idx->hh.next))
                        {
                            if (contains(c_pos_idxes[diff_char_idx][diff_pos], r_child_idx->val))
                            {
                                r_child_idxes = remove_val(r_child_idxes, r_child_idx->val);
                            }
                        }
                    }
                }
                pos++;
            }
            if (r_child_idxes != NULL)
            {
                if (nodes[i]->children_size == 0)
                {
                    nodes[i]->children = malloc(sizeof(struct WordTreeNode *) * HASH_COUNT(r_child_idxes));
                }
                else
                {
                    nodes[i]->children = realloc(nodes[i]->children,
                                                 sizeof(struct WordTreeNode *) * (HASH_COUNT(r_child_idxes) + nodes[i]->children_size));
                }
                struct IntSet *r_child_idx;
                for (r_child_idx = r_child_idxes; r_child_idx != NULL;
                     r_child_idx = (struct IntSet *)(r_child_idx->hh.next))
                {
                    if (idx_nodes[r_child_idx->val] == NULL)
                    {
                        idx_nodes[r_child_idx->val] = malloc(sizeof(struct WordTreeNode));
                        idx_nodes[r_child_idx->val]->word = words[r_child_idx->val];
                        idx_nodes[r_child_idx->val]->word_idx = r_child_idx->val;
                        idx_nodes[r_child_idx->val]->children_size = 0;
                        idx_nodes[r_child_idx->val]->parent_size = 0;
                        idx_nodes[r_child_idx->val]->parents = malloc(sizeof(struct WordTreeNode *) * (*node_size));
                    }
                    if (r_child_idx->val == end_word_idx)
                    {
                        (*has_find_end) = true;
                    }
                    struct WordTreeNode *child_node = idx_nodes[r_child_idx->val];
                    child_node->parents[child_node->parent_size++] = nodes[i];
                    nodes[i]->children[nodes[i]->children_size++] = child_node;
                    child_idxes = add_int(child_idxes, r_child_idx->val);
                }
                r_child_idxes = remove_all(r_child_idxes);
            }
        }
    }

    (*node_size) = 0;
    if ((*has_find_end))
    {
        return nodes;
    }
    if (child_idxes != NULL)
    {
        nodes = realloc(nodes, sizeof(struct WordTreeNode *) * HASH_COUNT(child_idxes));
        struct IntSet *child_idx;
        for (child_idx = child_idxes; child_idx != NULL;
             child_idx = (struct IntSet *)(child_idx->hh.next))
        {
            nodes[(*node_size)++] = idx_nodes[child_idx->val];
            used[child_idx->val] = true;
            for (int i = 0; i < word_len; i++)
            {
                int char_idx = words[child_idx->val][i] - 'a';
                c_pos_idxes[char_idx][i] = remove_val(c_pos_idxes[char_idx][i], child_idx->val);
            }
        }
        child_idxes = remove_all(child_idxes);
    }

    return nodes;
}

struct Ladders *build_ladders(struct WordTreeNode *node, int terminal_idx)
{
    struct Ladders *ladders = NULL;
    if (node->word_idx == terminal_idx)
    {
        ladders = malloc(sizeof(struct Ladders));
        ladders->ladder_size = 1;
        ladders->ladders = malloc(sizeof(struct Ladder *));
        ladders->ladders[0] = malloc(sizeof(struct Ladder));
        ladders->ladders[0]->word_size = 1;
        ladders->ladders[0]->words = malloc(sizeof(char *));
        ladders->ladders[0]->words[0] = node->word;
    }
    else
    {
        if (node->children_size > 0)
        {
            ladders = malloc(sizeof(struct Ladders));
            ladders->ladder_size = 0;
            for (int i = 0; i < node->children_size; i++)
            {
                struct Ladders *child_ladders = build_ladders(node->children[i], terminal_idx);
                if (child_ladders != NULL)
                {
                    if (child_ladders->ladder_size > 0)
                    {
                        if (ladders->ladder_size == 0)
                        {
                            ladders->ladders = malloc(sizeof(struct Ladder *) * child_ladders->ladder_size);
                        }
                        else
                        {
                            ladders->ladders = realloc(ladders->ladders,
                                                       sizeof(struct Ladder *) *
                                                           (ladders->ladder_size + child_ladders->ladder_size));
                        }
                        for (int j = 0; j < child_ladders->ladder_size; j++)
                        {
                            struct Ladder *child_ladder = child_ladders->ladders[j];
                            ladders->ladders[ladders->ladder_size++] = malloc(sizeof(struct Ladder));
                            ladders->ladders[ladders->ladder_size - 1]->word_size = child_ladder->word_size + 1;
                            ladders->ladders[ladders->ladder_size - 1]->words =
                                malloc(sizeof(char *) * (child_ladder->word_size + 1));
                            for (int k = 0; k < child_ladder->word_size; k++)
                            {
                                ladders->ladders[ladders->ladder_size - 1]->words[k + 1] = child_ladder->words[k];
                            }
                            ladders->ladders[ladders->ladder_size - 1]->words[0] = node->word;
                        }
                    }
                }
            }
        }
    }
    return ladders;
}

char ***findLadders(char *beginWord, char *endWord,
                    char **wordList, int wordListSize,
                    int *returnSize, int **returnColumnSizes)
{
    int word_len = strlen(beginWord);

    if (word_len == 1)
    {
        (*returnSize) = 1;
        (*returnColumnSizes) = malloc(sizeof(int));
        (*returnColumnSizes)[0] = 2;
        char ***ladders = malloc(sizeof(char **));
        ladders[0] = malloc(sizeof(char *) * 2);
        ladders[0][0] = beginWord;
        ladders[0][1] = endWord;
        return ladders;
    }

    bool *used = calloc(wordListSize, sizeof(bool));
    struct IntSet ***c_pos_idxes = calloc(CHAR_SIZE, sizeof(struct IntSet **));
    int end_word_idx = -1;
    for (int idx = 0; idx < wordListSize; idx++)
    {
        if (strcmp(beginWord, wordList[idx]) == 0)
        {
            used[idx] = true;
            continue;
        }
        for (int pos = 0; pos < word_len; pos++)
        {
            int char_idx = wordList[idx][pos] - 'a';
            if (c_pos_idxes[char_idx] == NULL)
            {
                c_pos_idxes[char_idx] = calloc(word_len, sizeof(struct IntSet *));
            }
            c_pos_idxes[char_idx][pos] = add_int(c_pos_idxes[char_idx][pos], idx);
        }
        if (end_word_idx == -1 && strcmp(wordList[idx], endWord) == 0)
        {
            end_word_idx = idx;
        }
    }

    struct WordTreeNode *root = malloc(sizeof(struct WordTreeNode));
    root->word = beginWord;
    root->word_idx = -1;
    root->children_size = 0;

    struct WordTreeNode **idx_nodes = calloc(wordListSize, sizeof(struct WordTreeNode *));
    struct WordTreeNode **nodes = malloc(sizeof(struct WordTreeNode *));
    int *node_size = calloc(1, sizeof(int));
    (*node_size) = 1;
    nodes[(*node_size) - 1] = root;

    bool *has_find_end = calloc(1, sizeof(bool));
    while ((*node_size) > 0)
    {
        nodes = build_children(nodes, node_size, c_pos_idxes, used, end_word_idx, has_find_end, word_len, wordList, idx_nodes);
    }
    if (root->children_size == 0 || !(*has_find_end))
    {
        (*returnSize) = 0;
        return NULL;
    }

    struct Ladders *root_ladders = build_ladders(root, end_word_idx);
    char ***ladders = malloc(sizeof(char **) * root_ladders->ladder_size);
    (*returnSize) = root_ladders->ladder_size;
    returnColumnSizes[0] = malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < (*returnSize); i++)
    {
        (*returnColumnSizes)[i] = root_ladders->ladders[i]->word_size;
        ladders[i] = malloc(sizeof(char *) * root_ladders->ladders[i]->word_size);
        for (int j = 0; j < root_ladders->ladders[i]->word_size; j++)
        {
            ladders[i][j] = root_ladders->ladders[i]->words[j];
        }
    }
    return ladders;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *beginWord = "lost", *endWord = "miss";
    int wordListSize = 6;
    char **wordList = malloc(sizeof(char *) * wordListSize);
    wordList[0] = "most";
    wordList[1] = "mist";
    wordList[2] = "miss";
    wordList[3] = "lost";
    wordList[4] = "fist";
    wordList[5] = "fish";
    int *returnSize = malloc(sizeof(int));
    int **returnColumnSizes = malloc(sizeof(int *));
    char ***ladders = findLadders(beginWord, endWord,
                                  wordList, wordListSize,
                                  returnSize, returnColumnSizes);
    for (int i = 0; i < (*returnSize); i++)
    {
        printf("%d's,[", i);
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%s,", ladders[i][j]);
        }
        printf("]\n");
    }

    return 0;
}