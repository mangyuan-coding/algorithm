/*
 * @lc app=leetcode id=22 lang=c
 *
 * [22] Generate Parentheses
 */
// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

// (a)b -> a , b can be empty
// n = 1
// a = 0 b = 0  ()
// n = 2
// a = 0 b = 1  ()()
// a = 1 b = 0  (())
// n = 3
// a = 0 b = 2 b -> ()() (())
// ()()() ()(())
// a = 1 b = 1
// (())()
// a = 2 b = 0 a -> ()() (())
// (()()) ((()))
// so
// n = 1, ()
// n = 2, ()() (())
// n = 3, ()()() ()(()) (())() (()()) ((()))
// n = 4, ()()()() ()()(()) ()(())() ()(()()) ()((())) (())()() (())(()) (()())() ((()))() (()()()) (()(())) ((())()) ((()())) (((())))
// a = 0 b = 3 ()()()() ()()(()) ()(())() ()(()()) ()((()))
// a = 1 b = 2 (())()() (())(())
// a = 2 b = 1 (()())() ((()))()
// a = 3 b = 0 (()()()) (()(())) ((())()) ((()())) (((())))
char **generateParenthesis(int n, int *returnSize)
{

    char ***ret = (char ***)malloc(sizeof(char **) * n);
    int *ret_size = (int *)malloc(sizeof(int) * n);
    ret[0] = (char **)malloc(sizeof(char *));
    ret[0][0] = "()";
    ret_size[0] = 1;

    if (n == 1)
    {
        *returnSize = ret_size[0];
        return ret[0];
    }

    ret[1] = (char **)malloc(sizeof(char *) * 2);
    ret[1][0] = "()()";
    ret[1][1] = "(())";
    ret_size[1] = 2;

    if (n == 2)
    {
        *returnSize = ret_size[1];
        return ret[1];
    }

    for (int i = 2; i < n; i++)
    {
        int char_size = (i + 1) * 2 + 1;

        ret[i] = (char **)malloc(sizeof(char *));
        ret_size[i] = 0;
        for (int a = 0; a <= i; a++)
        {
            if (a == 0)
            {
                // ()b
                char **b_arr = ret[i - 1];
                int b_size = ret_size[i - 1];
                ret[i] = (char **)realloc(ret[i], sizeof(char *) * (ret_size[i] + b_size));
                for (int k = 0; k < b_size; k++)
                {
                    ret[i][ret_size[i]] = (char *)malloc(sizeof(char) * char_size);
                    ret[i][ret_size[i]][0] = '(';
                    ret[i][ret_size[i]][1] = ')';
                    ret[i][ret_size[i]][char_size - 1] = '\0';
                    strcpy(ret[i][ret_size[i]] + 2, b_arr[k]);
                    ret_size[i]++;
                }
            }
            else if (a == i)
            {
                // (a)
                char **a_arr = ret[i - 1];
                int a_size = ret_size[i - 1];
                ret[i] = (char **)realloc(ret[i], sizeof(char *) * (ret_size[i] + a_size));
                for (int k = 0; k < a_size; k++)
                {
                    ret[i][ret_size[i]] = (char *)malloc(sizeof(char) * char_size);
                    ret[i][ret_size[i]][char_size - 1] = '\0';
                    ret[i][ret_size[i]][0] = '(';
                    strcpy(ret[i][ret_size[i]] + 1, a_arr[k]);
                    ret[i][ret_size[i]][char_size - 2] = ')';
                    ret_size[i]++;
                }
            }
            else
            {
                // (a)b
                char **a_arr = ret[a - 1];
                int a_size = ret_size[a - 1];

                char **b_arr = ret[i - a - 1];
                int b_size = ret_size[i - a - 1];

                ret[i] = (char **)realloc(ret[i], sizeof(char *) * (ret_size[i] + a_size * b_size));
                for (int j = 0; j < a_size; j++)
                {
                    for (int k = 0; k < b_size; k++)
                    {
                        /* code */
                        ret[i][ret_size[i]] = (char *)malloc(sizeof(char) * char_size);
                        ret[i][ret_size[i]][char_size - 1] = '\0';
                        ret[i][ret_size[i]][0] = '(';

                        int a_size = a * 2;
                        strcpy(ret[i][ret_size[i]] + 1, a_arr[j]);

                        ret[i][ret_size[i]][a_size + 1] = ')';

                        strcpy(ret[i][ret_size[i]] + a_size + 2, b_arr[k]);
                        ret_size[i]++;
                    }
                }
            }
        }
    }

    *returnSize = ret_size[n - 1];
    return ret[n - 1];
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *returnSize = malloc(sizeof(int));
    char **ret = generateParenthesis(4, returnSize);

    for (int i = 0; i < *returnSize; i++)
    {
        printf("ret is  %s \n", ret[i]);
    }

    return 0;
}
