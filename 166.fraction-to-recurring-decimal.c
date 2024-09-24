/*
 * @lc app=leetcode.cn id=166 lang=c
 *
 * [166] Fraction to Recurring Decimal
 *
 * https://leetcode.cn/problems/fraction-to-recurring-decimal/description/
 *
 * algorithms
 * Medium (33.53%)
 * Likes:    500
 * Dislikes: 0
 * Total Accepted:    71.9K
 * Total Submissions: 214.4K
 * Testcase Example:  '1\n2'
 *
 * Given two integers representing the numerator and denominator of a fraction,
 * return the fraction in string format.
 *
 * If the fractional part is repeating, enclose the repeating part in
 * parentheses.
 *
 * If multiple answers are possible, return any of them.
 *
 * It is guaranteed that the length of the answer string is less than 10^4 for
 * all the given inputs.
 *
 *
 * Example 1:
 *
 *
 * Input: numerator = 1, denominator = 2
 * Output: "0.5"
 *
 *
 * Example 2:
 *
 *
 * Input: numerator = 2, denominator = 1
 * Output: "2"
 *
 *
 * Example 3:
 *
 *
 * Input: numerator = 4, denominator = 333
 * Output: "0.(012)"
 *
 *
 *
 * Constraints:
 *
 *
 * -2^31 <= numerator, denominator <= 2^31 - 1
 * denominator != 0
 *
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "uthash/src/uthash.h"

// @lc code=start

typedef struct Link
{
    char key[256];
    int idx;
    UT_hash_handle hh;
} Link;

struct Link *find_link(struct Link *link, char *key)
{
    struct Link *finded;
    HASH_FIND_STR(link, key, finded);
    return finded;
}

struct Link *add_link(struct Link *link, char *key, int idx)
{
    struct Link *finded = find_link(link, key);
    if (finded == NULL)
    {
        finded = malloc(sizeof(struct Link));
        finded->idx = idx;
        strcpy(finded->key, key);
        HASH_ADD_STR(link, key, finded);
    }
    return link;
}

char *fractionToDecimal(int numerator, int denominator)
{

    if (numerator == 0)
    {
        return "0";
    }

    char *ret = calloc(10000, sizeof(char));

    int ret_size = 0;
    long num = numerator, deno = denominator;

    long integer = num / deno;
    if (integer < 0)
    {
        integer = -integer;
    }

    bool neg = denominator < 0 && numerator > 0 || (denominator > 0 && numerator < 0);
    if (neg)
    {
        ret[ret_size++] = '-';
    }

    while (integer >= 10)
    {
        ret[ret_size++] = integer % 10 + '0';
        integer /= 10;
    }
    ret[ret_size++] = integer + '0';

    int start = neg ? 1 : 0, end = ret_size - 1;
    char temp;
    while (start < end)
    {
        temp = ret[start];
        ret[start] = ret[end];
        ret[end] = temp;
        start++;
        end--;
    }

    if (denominator < 0)
    {
        deno = -deno;
    }

    struct Link *link;

    long remain = num % deno;
    if (remain == 0)
    {
        ret[ret_size++] = '\0';
        return ret;
    }
    if (remain < 0)
    {
        remain = -remain;
    }
    ret[ret_size++] = '.';
    char key[256];
    sprintf(key, "%ld", remain - 1);
    link = add_link(link, key, ret_size);

    struct Link *finded;
    while (true)
    {
        remain *= 10;
        if (remain < deno)
        {
            ret[ret_size++] = '0';
        }
        else
        {
            ret[ret_size++] = remain / deno + '0';
            remain %= deno;
        }
        if (remain == 0)
        {
            break;
        }

        char find_key[256];
        sprintf(find_key, "%ld", remain - 1);
        finded = find_link(link, find_key);
        if (finded != NULL)
        {
            break;
        }

        char key[256];
        sprintf(key, "%ld", remain - 1);
        link = add_link(link, key, ret_size);
    }

    if (remain == 0)
    {
        ret[ret_size++] = '\0';
        return ret;
    }
    ret_size += 2;
    ret[ret_size - 1] = ')';
    for (int i = ret_size - 2; i > finded->idx; i--)
    {
        ret[i] = ret[i - 1];
    }
    ret[finded->idx] = '(';
    ret[ret_size++] = '\0';
    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%s", fractionToDecimal(-50, 8));
    return 0;
}
