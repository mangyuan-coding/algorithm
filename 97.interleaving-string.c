/*
 * @lc app=leetcode.cn id=97 lang=c
 *
 * [97] Interleaving String
 */
#include <stdbool.h>
#include <stdio.h>

// @lc code=start
#include <string.h>
#include <stdlib.h>

// typedef struct tentative_point
// {
//     int idx_1;
//     int idx_2;
//     int idx_3;
// } tentative_point;

// bool isInterleave(char *s1, char *s2, char *s3)
// {
//     int len_1 = strlen(s1), len_2 = strlen(s2), len_3 = strlen(s3);

//     if (len_1 + len_2 != len_3)
//     {
//         return false;
//     }

//     if (len_1 == 0 && len_2 == 0)
//     {
//         return true;
//     }

//     int *s_c_size_1 = (int *)malloc(sizeof(int) * 26);
//     int *s_c_size_2 = (int *)malloc(sizeof(int) * 26);
//     int *s_c_size_3 = (int *)malloc(sizeof(int) * 26);
//     for (int i = 0; i < 26; i++)
//     {
//         s_c_size_1[i] = 0;
//         s_c_size_2[i] = 0;
//         s_c_size_3[i] = 0;
//     }

//     for (int i = 0; i < len_3; i++)
//     {
//         if (i < len_1)
//         {
//             s_c_size_1[s1[i] - 'a']++;
//         }
//         if (i < len_2)
//         {
//             s_c_size_2[s2[i] - 'a']++;
//         }
//         s_c_size_3[s3[i] - 'a']++;
//     }

//     for (int i = 0; i < 26; i++)
//     {
//         if (s_c_size_3[i] != s_c_size_1[i] + s_c_size_2[i])
//         {
//             return false;
//         }
//     }

//     int p_1 = 0, p_2 = 0, p_3 = 0;
//     // t = tentative
//     struct tentative_point **t_ps = (struct tentative_point **)malloc(sizeof(struct tentative_point *) * len_3);
//     for (int i = 0; i < len_3; i++)
//     {
//         t_ps[i] = (struct tentative_point *)malloc(sizeof(struct tentative_point));
//     }

//     int t_ps_size = 0;

//     while (p_3 < len_3)
//     {
//         if (s1[p_1] == s3[p_3])
//         {
//             if (s2[p_2] == s3[p_3])
//             {
//                 t_ps_size++;
//                 t_ps[t_ps_size - 1]->idx_1 = p_1;
//                 t_ps[t_ps_size - 1]->idx_2 = p_2;
//                 t_ps[t_ps_size - 1]->idx_3 = p_3;
//             }
//             p_1++;
//             p_3++;
//         }
//         else if (s2[p_2] == s3[p_3])
//         {
//             p_2++;
//             p_3++;
//         }
//         else
//         {
//             if (t_ps_size == 0)
//             {
//                 return false;
//             }
//             p_1 = t_ps[t_ps_size - 1]->idx_1;
//             p_2 = t_ps[t_ps_size - 1]->idx_2;
//             p_3 = t_ps[t_ps_size - 1]->idx_3;
//             t_ps_size--;
//             p_2++;
//             p_3++;
//         }
//     }

//     return true;
// }

bool isInterleave(char *s1, char *s2, char *s3)
{
    int len_1 = strlen(s1), len_2 = strlen(s2), len_3 = strlen(s3);
    if (len_1 + len_2 != len_3)
    {
        return false;
    }

    if (len_1 == 0 && len_2 == 0)
    {
        return true;
    }

    bool **interleave = (bool **)malloc(sizeof(bool *) * (len_1 + 1));
    for (int i = 0; i < len_1 + 1; i++)
    {
        interleave[i] = (bool *)malloc(sizeof(bool) * (len_2 + 1));
        memset(interleave[i], false, sizeof(bool));
    }

    for (int i = 0; i <= len_1; i++)
    {
        for (int j = 0; j <= len_2; j++)
        {
            if (i == 0 && j == 0)
            {
                interleave[i][j] = true;
            }
            else if (i == 0)
            {
                interleave[i][j] = s2[j - 1] == s3[i + j - 1] && interleave[i][j - 1];
            }
            else if (j == 0)
            {
                interleave[i][j] = s1[i - 1] == s3[i + j - 1] && interleave[i - 1][j];
            }
            else
            {
                interleave[i][j] = (s1[i - 1] == s3[i + j - 1] && interleave[i - 1][j]) || (s2[j - 1] == s3[i + j - 1] && interleave[i][j - 1]);
            }
        }
    }

    return interleave[len_1][len_2];
}

// @lc code=end
int main(int argc, char const *argv[])
{
    bool ret = isInterleave("aabcc",
                            "dbbca",
                            "aadbbcbcac");
    return 0;
}
