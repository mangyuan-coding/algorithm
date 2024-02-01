/*
 * @lc app=leetcode id=168 lang=c
 *
 * [168] Excel Sheet Column Title
 */

// @lc code=start
#include <stdlib.h>

char *convertToTitle(int columnNumber)
{
    int lv = 1;
    int lv_factor = 26;
    int lv_max = 26;
    while (columnNumber > lv_max && lv_factor < 308915776)
    {
        lv++;
        lv_factor *= 26;
        lv_max = lv_factor + lv_max;
    }
    if (columnNumber > lv_max)
    {
        lv++;
    }
    else
    {
        lv_factor /= 26;
    }

    char *col_name = (char *)malloc(sizeof(char) * (lv + 1));
    int col_idx = 0;

    while (columnNumber >= 0)
    {
        if (lv_factor == 0)
        {
            break;
        }
        int w = columnNumber / lv_factor;
        if (w == 0)
        {
            col_name[col_idx - 1] -= 1;
            col_name[col_idx++] = 'Z';
            if (lv_factor == 1)
            {
                break;
            }
        }
        else
        {
            col_name[col_idx++] = 'A' + (w - 1);
            columnNumber -= w * lv_factor;
        }
        lv_factor /= 26;
    }
    col_name[col_idx] = '\0';
    return col_name;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%s", convertToTitle(1));
    return 0;
}
