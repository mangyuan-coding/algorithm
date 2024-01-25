/*
 * @lc app=leetcode id=72 lang=c
 *
 * [72] Edit Distance
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int minDistance(char *word1, char *word2)
{
    int len_o = strlen(word1);
    int len_t = strlen(word2);
    if (len_o == 0 && len_t == 0)
    {
        return 0;
    }
    if (len_o == 0)
    {
        return len_t;
    }
    if (len_t == 0)
    {
        return len_o;
    }

    int **min_step = (int **)malloc(sizeof(int *) * (len_o + 1));
    for (int i = 0; i <= len_o; i++)
    {
        min_step[i] = (int *)malloc(sizeof(int) * (len_t + 1));
    }

    for (int i = len_o; i >= 0; i--)
    {
        for (int j = len_t; j >= 0; j--)
        {
            if (i == len_o)
            {
                min_step[i][j] = len_t - j;
            }
            else if (j == len_t)
            {
                min_step[i][j] = len_o - i;
            }
            else
            {
                int cur_min_step = len_o + len_t;
                int step;

                bool same_char = word1[i] == word2[j];

                // replase or nothing
                step = 0;
                if (!same_char)
                {
                    step++;
                }
                step += min_step[i + 1][j + 1];
                if (step < cur_min_step)
                {
                    cur_min_step = step;
                }

                // insert
                step = 1;
                step += min_step[i][j + 1];
                if (step < cur_min_step)
                {
                    cur_min_step = step;
                }

                // delete
                step = 1;
                step += min_step[i + 1][j];
                if (step < cur_min_step)
                {
                    cur_min_step = step;
                }

                min_step[i][j] = cur_min_step;
            }
        }
    }

    return min_step[0][0];
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%d", minDistance("dinitrophenylhydrazine", "acetylphenylhydrazine"));
    return 0;
}
