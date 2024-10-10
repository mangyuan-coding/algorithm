/*
 * @lc app=leetcode.cn id=187 lang=c
 *
 * [187] Repeated DNA Sequences
 *
 * https://leetcode.cn/problems/repeated-dna-sequences/description/
 *
 * algorithms
 * Medium (55.15%)
 * Likes:    597
 * Dislikes: 0
 * Total Accepted:    180K
 * Total Submissions: 326.4K
 * Testcase Example:  '"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"'
 *
 * The DNA sequence is composed of a series of nucleotides abbreviated as 'A',
 * 'C', 'G', and 'T'.
 *
 *
 * For example, "ACGAATTCCG" is a DNA sequence.
 *
 *
 * When studying DNA, it is useful to identify repeated sequences within the
 * DNA.
 *
 * Given a string s that represents a DNA sequence, return all the
 * 10-letter-long sequences (substrings) that occur more than once in a DNA
 * molecule. You may return the answer in any order.
 *
 *
 * Example 1:
 * Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * Output: ["AAAAACCCCC","CCCCCAAAAA"]
 * Example 2:
 * Input: s = "AAAAAAAAAAAAA"
 * Output: ["AAAAAAAAAA"]
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^5
 * s[i] is either 'A', 'C', 'G', or 'T'.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash/src/uthash.h"

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct array
{
    char *chars;
    UT_hash_handle hh;
} string;

char **findRepeatedDnaSequences(char *s, int *returnSize)
{
    (*returnSize) = 0;
    int len = strlen(s);
    if (len <= 10)
    {
        return NULL;
    }

    string *set = NULL, *sames = NULL;

    char *str;
    string *exist, *new;
    for (int i = 0; i <= len - 10; i++)
    {
        str = malloc(sizeof(char) * 11);
        strncpy(str, s + i, sizeof(char) * 11);
        str[10] = '\0';

        HASH_FIND_STR(set, str, exist);
        if (exist == NULL)
        {
            new = (string *)malloc(sizeof(string));
            new->chars = str;
            HASH_ADD_STR(set, chars, new);
        }
        else
        {
            HASH_FIND_STR(sames, str, new);
            if (new == NULL)
            {
                new = (string *)malloc(sizeof(string));
                new->chars = str;
                HASH_ADD_STR(sames, chars, new);
            }
        }
    }

    char **sequences = malloc(sizeof(char *) * HASH_COUNT(sames));
    for (exist = sames; exist != NULL; exist = exist->hh.next)
    {
        (*returnSize)++;
        sequences[(*returnSize) - 1] = exist->chars;
    }
    return sequences;
}
// @lc code=end

int main(int argc, char const *argv[])
{
    int *returnSize = malloc(sizeof(int));
    char **sequences = findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT", returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%s \n", sequences[i]);
    }

    return 0;
}
