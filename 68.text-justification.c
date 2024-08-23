/*
 * @lc app=leetcode.cn id=68 lang=c
 *
 * [68] Text Justification
 *
 * https://leetcode.cn/problems/text-justification/description/
 *
 * algorithms
 * Hard (54.59%)
 * Likes:    432
 * Dislikes: 0
 * Total Accepted:    86.2K
 * Total Submissions: 157.9K
 * Testcase Example:  '["This", "is", "an", "example", "of", "text", "justification."]\n16'
 *
 * Given an array of strings words and a width maxWidth, format the text such
 * that each line has exactly maxWidth characters and is fully (left and right)
 * justified.
 *
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly maxWidth characters.
 *
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line does not divide evenly between words, the
 * empty slots on the left will be assigned more spaces than the slots on the
 * right.
 *
 * For the last line of text, it should be left-justified, and no extra space
 * is inserted between words.
 *
 * Note:
 *
 *
 * A word is defined as a character sequence consisting of non-space characters
 * only.
 * Each word's length is guaranteed to be greater than 0 and not exceed
 * maxWidth.
 * The input array words contains at least one word.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: words = ["This", "is", "an", "example", "of", "text",
 * "justification."], maxWidth = 16
 * Output:
 * [
 * "This    is    an",
 * "example  of text",
 * "justification.  "
 * ]
 *
 * Example 2:
 *
 *
 * Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth
 * = 16
 * Output:
 * [
 * "What   must   be",
 * "acknowledgment  ",
 * "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall
 * be", because the last line must be left-justified instead of
 * fully-justified.
 * Note that the second line is also left-justified because it contains only
 * one word.
 *
 * Example 3:
 *
 *
 * Input: words =
 * ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"],
 * maxWidth = 20
 * Output:
 * [
 * "Science  is  what we",
 * ⁠ "understand      well",
 * "enough to explain to",
 * "a  computer.  Art is",
 * "everything  else  we",
 * "do                  "
 * ]
 *
 *
 * Constraints:
 *
 *
 * 1 <= words.length <= 300
 * 1 <= words[i].length <= 20
 * words[i] consists of only English letters and symbols.
 * 1 <= maxWidth <= 100
 * words[i].length <= maxWidth
 *
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fullJustify(char **words, int wordsSize, int maxWidth, int *returnSize)
{
    (*returnSize) = 0;
    char **lines = malloc(sizeof(char *) * wordsSize);

    int start = 0, end, cur = 0, pending_len = 0, pending_size, slot_size, *slots, slot_idx, word_len;

    while (1)
    {
        word_len = strlen(words[cur]);
        if (pending_len + word_len + (cur - start) > maxWidth)
        {
            (*returnSize)++;
            lines[(*returnSize) - 1] = malloc(sizeof(char) * (maxWidth + 1));

            end = cur - 1;
            pending_size = end - start + 1;
            if (pending_size == 1)
            {
                int copy_len = strlen(words[start]);
                memcpy(lines[(*returnSize) - 1], words[start], sizeof(char) * copy_len);
                for (int i = copy_len; i < maxWidth; i++)
                {
                    lines[(*returnSize) - 1][i] = ' ';
                }
            }
            else
            {
                slot_size = pending_size - 1;
                slots = malloc(sizeof(int) * slot_size);
                for (int i = 0; i < slot_size; i++)
                {
                    slots[i] = 0;
                }
                for (int i = 0, slot_idx = 0; i < maxWidth - pending_len; i++)
                {
                    slots[slot_idx % slot_size]++;
                    slot_idx++;
                }
                for (int i = 0, size = 0, cpy_len; i < pending_size + slot_size; i++)
                {
                    if (i % 2 == 0)
                    {
                        cpy_len = strlen(words[start + i / 2]);
                        memcpy(lines[(*returnSize) - 1] + size, words[start + i / 2], sizeof(char) * cpy_len);
                        size += cpy_len;
                    }
                    else
                    {
                        for (int j = 0; j < slots[i / 2]; j++)
                        {
                            lines[(*returnSize) - 1][size++] = ' ';
                        }
                    }
                }
            }
            lines[(*returnSize) - 1][maxWidth] = '\0';

            start = cur;
            pending_len = 0;
        }
        else if (cur == wordsSize - 1)
        {
            (*returnSize)++;
            lines[(*returnSize) - 1] = malloc(sizeof(char) * (maxWidth + 1));
            pending_size = cur - start;
            int line_idx = 0;
            for (int cpy_len; start <= cur; start++)
            {
                cpy_len = strlen(words[start]);
                memcpy(lines[(*returnSize) - 1] + line_idx, words[start], sizeof(char) * cpy_len);
                line_idx += cpy_len;
                lines[(*returnSize) - 1][line_idx++] = ' ';
            }
            for (; line_idx < maxWidth; line_idx++)
            {
                lines[(*returnSize) - 1][line_idx] = ' ';
            }

            lines[(*returnSize) - 1][maxWidth] = '\0';
            break;
        }
        else
        {
            pending_len += word_len;
            cur++;
        }
    }
    return lines;
}
// @lc code=end

int main(int argc, char const *argv[])
{
    int wordsSize = 7;
    char **words = malloc(sizeof(char *) * wordsSize);
    words[0] = "This";
    words[1] = "is";
    words[2] = "an";
    words[3] = "example";
    words[4] = "of";
    words[5] = "text";
    words[6] = "justification.";
    int maxWidth = 16;
    int *returnSize = malloc(sizeof(int));
    char **lines = fullJustify(words, wordsSize, maxWidth, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%s \n", lines[i]);
    }
    return 0;
}
