/*
 * @lc app=leetcode.cn id=131 lang=c
 *
 * [131] Palindrome parting
 */
#include <stdio.h>
// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct palindrome
{
    char *p;
} palindrome;

typedef struct part
{
    int size;
    struct palindrome **ps;
} part;

typedef struct p_group
{
    int size;
    struct part **ps;
} p_group;

bool is_palindrome(char *s, int start, int end)
{
    while (start < end)
    {
        if (s[start] != s[end])
        {
            return false;
        }
        start++;
        end--;
    }

    return true;
}

char ***partition(char *s, int *returnSize, int **returnColumnSizes)
{
    int len = strlen(s);
    bool **idx_palindromes = (bool **)malloc(sizeof(bool *) * len);
    for (int i = 0; i < len; i++)
    {
        idx_palindromes[i] = (bool *)malloc(sizeof(bool) * len);
        for (int j = i; j < len; j++)
        {
            if (is_palindrome(s, i, j))
            {
                idx_palindromes[i][j] = true;
            }
            else
            {
                idx_palindromes[i][j] = false;
            }
        }
    }

    // // n level palindromes n array
    // char ****n_p = (char ****)malloc(sizeof(char ***) * len);
    // // n level group size
    // int *n_p_g = (int *)malloc(sizeof(int) * len);
    // // n level group substring size
    // int **n_p_g_s = (int **)malloc(sizeof(int *) * len);
    struct p_group **n = (struct p_group **)malloc(sizeof(struct p_group *) * len);
    // // init 0
    // n_p_g[0] = 1;
    // n_p_g_s[0] = (int *)malloc(sizeof(int));
    // n_p_g_s[0][0] = 1;
    // n_p[0] = (char ***)malloc(sizeof(char **));
    // n_p[0][0] = (char **)malloc(sizeof(char *));
    // n_p[0][0][0] = (char *)malloc(sizeof(char) * 2);
    // n_p[0][0][0][0] = s[0];
    // n_p[0][0][0][1] = '\0';
    n[0] = (struct p_group *)malloc(sizeof(struct p_group));
    n[0]->size = 1;
    n[0]->ps = (struct part **)malloc(sizeof(struct part *));
    n[0]->ps[0] = (struct part *)malloc(sizeof(struct part));
    n[0]->ps[0]->size = 1;
    n[0]->ps[0]->ps = (struct palindrome **)malloc(sizeof(struct palindrome *));
    n[0]->ps[0]->ps[0] = (struct palindrome *)malloc(sizeof(struct palindrome));
    n[0]->ps[0]->ps[0]->p = (char *)malloc(sizeof(char) * 2);
    n[0]->ps[0]->ps[0]->p[0] = s[0];
    n[0]->ps[0]->ps[0]->p[1] = '\0';

    int pre_sum = 1;
    for (int i = 1; i < len; i++)
    {
        n[i] = (struct p_group *)malloc(sizeof(struct p_group));
        n[i]->size = 0;

        n[i]->ps = (struct part **)malloc(sizeof(struct part *) * (pre_sum + 1));
        for (int j = i; j >= 0; j--)
        {

            if (idx_palindromes[j][i])
            {

                if (j == 0)
                {
                    n[i]->size++;
                    n[i]->ps[n[i]->size - 1] = (struct part *)malloc(sizeof(struct part));
                    n[i]->ps[n[i]->size - 1]->size = 1;
                    n[i]->ps[n[i]->size - 1]->ps = (struct palindrome **)malloc(sizeof(struct palindrome *));
                    n[i]->ps[n[i]->size - 1]->ps[0] = (struct palindrome *)malloc(sizeof(struct palindrome));
                    n[i]->ps[n[i]->size - 1]->ps[0]->p = (char *)malloc(sizeof(char) * (i + 2));
                    memcpy(n[i]->ps[n[i]->size - 1]->ps[0]->p, s, sizeof(char) * (i + 1));
                    n[i]->ps[n[i]->size - 1]->ps[0]->p[i + 1] = '\0';

                    pre_sum++;
                }
                else
                {
                    int palindromes_size = i - j;
                    // f(j - 1) + [i]
                    for (int g = 0; g < n[j - 1]->size; g++)
                    {
                        n[i]->size++;
                        n[i]->ps[n[i]->size - 1] = (struct part *)malloc(sizeof(struct part));
                        n[i]->ps[n[i]->size - 1]->size = 0;
                        n[i]->ps[n[i]->size - 1]->ps = (struct palindrome **)malloc(sizeof(struct palindrome *) * (n[j - 1]->ps[g]->size + 1));
                        for (int sub = 0; sub < n[j - 1]->ps[g]->size; sub++)
                        {
                            n[i]->ps[n[i]->size - 1]->size++;

                            int sub_string_len = strlen(n[j - 1]->ps[g]->ps[sub]->p);

                            n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1] = (struct palindrome *)malloc(sizeof(struct palindrome));
                            n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1]->p = (char *)malloc(sizeof(char) * (sub_string_len + 1));
                            memcpy(n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1]->p, n[j - 1]->ps[g]->ps[sub]->p, sizeof(char) * sub_string_len);
                            n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1]->p[sub_string_len] = '\0';
                        }
                        n[i]->ps[n[i]->size - 1]->size++;
                        n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1] = (struct palindrome *)malloc(sizeof(struct palindrome));
                        n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1]->p = (char *)malloc(sizeof(char) * (i - j + 2));
                        memcpy(n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1]->p, s + j, sizeof(char) * (i - j + 1));
                        n[i]->ps[n[i]->size - 1]->ps[n[i]->ps[n[i]->size - 1]->size - 1]->p[i - j + 1] = '\0';
                        pre_sum++;
                    }
                }
            }
        }
    }

    *returnSize = n[len - 1]->size;
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    char ***ret = (char ***)malloc(sizeof(char **) * (*returnSize));

    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = n[len - 1]->ps[i]->size;
        ret[i] = (char **)malloc(sizeof(char *) * ((*returnColumnSizes)[i]));
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            ret[i][j] = n[len - 1]->ps[i]->ps[j]->p;
        }
    }

    return ret;
}
// @lc code=end

int main(int argc, char const *argv[])
{

    char *s = (char *)malloc(sizeof(char) * 3);
    s = "aab";
    int *returnSize = (int *)malloc(sizeof(int));
    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    char ***palindromes = partation(s, returnSize, returnColumnSizes);

    printf("[");
    for (int i = 0; i < *returnSize; i++)
    {
        printf("[");
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%s,", palindromes[i][j]);
        }
        printf("],");
    }
    printf("]");
    return 0;
}
