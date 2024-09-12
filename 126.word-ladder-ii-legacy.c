/*
 * @lc app=leetcode.cn id=126 lang=c
 *
 * [126] Word Ladder II
 *
 * https://leetcode.cn/problems/word-ladder-ii/description/
 *
 * algorithms
 * Hard (36.73%)
 * Likes:    724
 * Dislikes: 0
 * Total Accepted:    60.8K
 * Total Submissions: 165.7K
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

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <time.h>

const int LETTER_SIZE = 26;
const char a = 'a';

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

bool only_one_char_diff(char *word_1, char *word_2, int word_len)
{
    bool has_diff = false;
    for (int i = 0; i < word_len; i++)
    {
        if (word_1[i] != word_2[i])
        {
            if (has_diff)
            {
                return false;
            }
            has_diff = true;
        }
    }
    return has_diff;
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

void rebuild_deep_nodes(struct WordTreeNode ***deep_nodes, int *deep_node_size, int deep)
{
    int left = 0, right = 0;
    while (right < deep_node_size[deep - 1])
    {
        if (deep_nodes[deep - 1][right]->children_size > 0)
        {
            deep_nodes[deep - 1][left++] = deep_nodes[right++];
        }
        else
        {
            right++;
        }
    }
    deep_node_size[deep - 1] = left + 1;
}

char ***findLadders(char *beginWord, char *endWord,
                    char **wordList, int wordListSize,
                    int *returnSize, int **returnColumnSizes)
{
    int word_len = strlen(beginWord);
    (*returnSize) = 0;

    bool *has_treed = calloc(wordListSize + 1, sizeof(bool));
    struct WordTreeNode **word_idx_nodes = calloc(wordListSize, sizeof(struct WordTreeNode *));

    int remian_word_size = 0;
    int *remian_word_idxes = calloc(wordListSize, sizeof(int));

    struct WordTreeNode *root = malloc(sizeof(struct WordTreeNode));
    root->word = beginWord;
    root->word_idx = -1;
    root->children_size = 0;
    root->children = malloc(sizeof(struct WordTreeNode *) * wordListSize);
    for (int i = 0; i < wordListSize; i++)
    {
        word_idx_nodes[i] = malloc(sizeof(struct WordTreeNode));
        word_idx_nodes[i]->word = wordList[i];
        word_idx_nodes[i]->word_idx = i;
        word_idx_nodes[i]->children = NULL;
        word_idx_nodes[i]->children_size = 0;
        word_idx_nodes[i]->parent_size = 0;
        word_idx_nodes[i]->parents = NULL;
        if (only_one_char_diff(beginWord, wordList[i], word_len))
        {
            root->children[root->children_size++] = word_idx_nodes[i];
            word_idx_nodes[i]->parents = malloc(sizeof(struct WordTreeNode *));
            word_idx_nodes[i]->parents[word_idx_nodes[i]->parent_size++] = root;
            if (strcmp(endWord, wordList[i]) == 0)
            {
                char ***ladders = calloc(1, sizeof(char **));
                (*returnSize)++;
                ladders[0] = calloc(2, sizeof(char *));
                ladders[0][0] = beginWord;
                ladders[0][1] = endWord;
                returnColumnSizes[0] = malloc(sizeof(int));
                (*returnColumnSizes)[0] = 2;
                return ladders;
            }
        }
        else if (strcmp(beginWord, wordList[i]) != 0)
        {
            remian_word_idxes[remian_word_size++] = i;
        }
    }

    if (root->children_size == 0)
    {
        return NULL;
    }

    int deep = 2;
    struct WordTreeNode ***deep_nodes = malloc(sizeof(struct WordTreeNode **) * wordListSize);
    int *deep_node_size = calloc(wordListSize, sizeof(int));
    deep_node_size[0] = 1;
    deep_node_size[1] = root->children_size;
    deep_nodes[0] = malloc(sizeof(struct WordTreeNode **));
    deep_nodes[0][0] = root;
    deep_nodes[1] = malloc(sizeof(struct WordTreeNode **) * root->children_size);
    for (int i = 0; i < root->children_size; i++)
    {
        deep_nodes[deep - 1][i] = root->children[i];
    }
    int **words_diff_record = calloc(wordListSize, sizeof(int *));
    for (int i = 0; i < wordListSize; i++)
    {
        words_diff_record[i] = calloc(wordListSize, sizeof(int));
    }

    bool has_find_end_word = false;
    struct WordTreeNode *end_word_node = NULL;
    bool *next_deep_word_idxs = calloc(wordListSize, sizeof(bool));

    int *temp_remian_word_idxes;
    int temp_remain_word_size;
    while (deep_node_size[deep - 1] > 0)
    {
        for (int i = 0; i < deep_node_size[deep - 1]; i++)
        {
            char *cur_word = deep_nodes[deep - 1][i]->word;
            int cur_word_idx = deep_nodes[deep - 1][i]->word_idx;
            for (int j = 0; j < remian_word_size; j++)
            {
                int word_idx = remian_word_idxes[j];
                if (only_one_char_diff(cur_word, wordList[word_idx], word_len))
                {
                    words_diff_record[cur_word_idx][word_idx] = 1;
                    next_deep_word_idxs[word_idx] = true;
                    if (strcmp(endWord, wordList[word_idx]) == 0)
                    {
                        has_find_end_word = true;
                        end_word_node = word_idx_nodes[word_idx];
                    }
                }
                else
                {
                    words_diff_record[cur_word_idx][word_idx] = -1;
                }
            }
        }

        for (int i = 0; i < remian_word_size; i++)
        {
            int word_idx = remian_word_idxes[i];
            for (int j = 0; j < deep_node_size[deep - 1]; j++)
            {
                int cur_word_idx = deep_nodes[deep - 1][j]->word_idx;
                if (words_diff_record[cur_word_idx][word_idx] == 1)
                {
                    if (deep_nodes[deep - 1][j]->children == NULL)
                    {
                        deep_nodes[deep - 1][j]->children = malloc(sizeof(struct WordTreeNode *) * remian_word_size);
                    }
                    deep_nodes[deep - 1][j]->children[deep_nodes[deep - 1][j]->children_size++] = word_idx_nodes[word_idx];
                    if (word_idx_nodes[word_idx]->parents == NULL)
                    {
                        word_idx_nodes[word_idx]->parents = malloc(sizeof(struct WordTreeNode *) * wordListSize);
                    }
                    word_idx_nodes[word_idx]->parents[word_idx_nodes[word_idx]->parent_size++] = deep_nodes[deep - 1][j];
                }
            }
        }

        rebuild_deep_nodes(deep_nodes, deep_node_size, deep);

        if (has_find_end_word)
        {
            break;
        }

        deep++;
        deep_node_size[deep - 1] = 0;
        deep_nodes[deep - 1] = malloc(sizeof(struct WordTreeNode **) * remian_word_size);
        temp_remain_word_size = 0;
        temp_remian_word_idxes = calloc(remian_word_size, sizeof(int));
        for (int i = 0; i < remian_word_size; i++)
        {
            int word_idx = remian_word_idxes[i];
            if (next_deep_word_idxs[word_idx])
            {
                next_deep_word_idxs[word_idx] = false;
                deep_nodes[deep - 1][deep_node_size[deep - 1]++] = word_idx_nodes[word_idx];
            }
            else
            {
                temp_remian_word_idxes[temp_remain_word_size++] = word_idx;
            }
        }
        free(remian_word_idxes);
        remian_word_size = temp_remain_word_size;
        remian_word_idxes = temp_remian_word_idxes;
    }

    if (!has_find_end_word)
    {
        return NULL;
    }

    struct Ladders *root_ladders = build_ladders(root, end_word_node->word_idx);

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
    char *beginWord = "hot", *endWord = "dog";
    int wordListSize = 8;
    char **wordList = malloc(sizeof(char *) * wordListSize);
    wordList[0] = "hot";
    wordList[1] = "cog";
    wordList[2] = "dog";
    wordList[3] = "tot";
    wordList[4] = "hog";
    wordList[5] = "hop";
    wordList[6] = "pot";
    wordList[7] = "dot";
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
