/*
 * @lc app=leetcode id=91 lang=c
 *
 * [91] Decode Ways
 */

// @lc code=start
#include <string.h>

int numDecodings(char *s)
{
    if (s[0] == '0')
    {
        return 0;
    }

    int len = strlen(s), pre = 1, pre_pre = 1, cur, pre_num, cur_num, num;
    for (int idx = 1; idx < len; idx++)
    {
        pre_num = s[idx - 1] - '0';
        cur_num = s[idx] - '0';
        num = pre_num * 10 + cur_num;
        if (num <= 26 && num >= 1)
        {
            if (cur_num == 0)
            {
                cur = pre_pre;
            }
            else if (pre_num == 0)
            {
                cur = pre;
            }
            else
            {
                cur = pre_pre + pre;
            }
        }
        else if (cur_num == 0)
        {
            return 0;
        }
        else
        {
            cur = pre;
        }

        // next indx
        pre_pre = pre;
        pre = cur;
    }
    return pre;
}
// @lc code=end
