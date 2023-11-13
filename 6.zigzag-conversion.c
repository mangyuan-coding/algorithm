/*
 * @lc app=leetcode id=6 lang=c
 *
 * [6] Zigzag Conversion
 */

// @lc code=start

#include <string.h>
#include <stdlib.h>

char *convert(char *s, int numRows)
{
    int len = strlen(s);
    if (len == 0 || len == 1 || numRows == 1)
    {
        return s;
    }

    char *ret = malloc(sizeof(char) * (len + 1));
    ret[len] = '\0';
    int ret_i = 0;

    // cycle length
    const int cyc_len = 2 * (numRows - 1);
    const int half_cyc_len = numRows - 1;
    // cycle times
    const int cyc_t = len / cyc_len + 1;

    for (int y = 0; y < numRows; y++)
    {
        for (int cyc_i = 0; cyc_i < cyc_t; cyc_i++)
        {
            /* code */
            // x1 = cyc_i * cyc_len
            // index = x1 + y
            int x1_index = cyc_i * cyc_len + y;
            if (x1_index < len)
            {
                ret[ret_i++] = s[x1_index];
            }
            // index = (cyc_i + 1) * cyc_len - y
            int x2_index = (cyc_i + 1) * cyc_len - y;
            if (x2_index < len && y != numRows - 1 && y != 0)
            {
                ret[ret_i++] = s[x2_index];
            }
        }
    }

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    char s[] = "PAYPALISHIRING";

    char *ret = convert(s, 3);

    printf_s(ret);

    return 0;
}
