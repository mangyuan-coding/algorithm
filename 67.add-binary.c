/*
 * @lc app=leetcode id=67 lang=c
 *
 * [67] Add Binary
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

const unsigned long long mask = 0x80000000;

char *addBinary(char *a, char *b)
{
    int len_a = strlen(a);
    int len_b = strlen(b);

    int bit_size_base = ((fmax(len_a, len_b) + 1) / 31) + 1;
    unsigned long long *bit_a = (unsigned long long *)malloc(sizeof(unsigned long long *) * bit_size_base);
    unsigned long long *bit_b = (unsigned long long *)malloc(sizeof(unsigned long long *) * bit_size_base);
    unsigned long long *bit_c = (unsigned long long *)malloc(sizeof(unsigned long long *) * bit_size_base);
    for (int i = 0; i < bit_size_base; i++)
    {
        bit_a[i] = 0x0;
        bit_b[i] = 0x0;
        bit_c[i] = 0x0;
    }

    int cur = bit_size_base;
    unsigned long long bit = 0x1;
    for (int i = len_a - 1, j = 0; i >= 0; i--, j++)
    {
        if (j % 31 == 0)
        {
            cur--;
            bit = 0x1;
        }
        if (a[i] == '1')
        {
            bit_a[cur] |= bit;
        }
        bit <<= 1;
    }

    cur = bit_size_base;
    for (int i = len_b - 1, j = 0; i >= 0; i--, j++)
    {
        if (j % 31 == 0)
        {
            cur--;
            bit = 0x1;
        }
        if (b[i] == '1')
        {
            bit_b[cur] |= bit;
        }
        bit <<= 1;
    }

    int ret_size = 0;
    int carry = 0x0;

    for (int i = bit_size_base - 1; i >= 0; i--)
    {
        bit_c[i] = bit_a[i] + bit_b[i] + carry;
        carry = (mask & bit_c[i]) > 0 ? 0x1 : 0x0;
    }

    char *ret = (char *)malloc(sizeof(char) * (fmax(len_a, len_b) + 2));
    int idx = 0;
    bool start = false;
    bit = 0x40000000;
    for (int i = 0; i < bit_size_base; i++)
    {
        for (int j = 1; j < 32; j++)
        {
            bool zero = (bit & bit_c[i]) == 0;
            bit >>= 1;
            if (zero && !start && idx == 0)
            {
                continue;
            }
            ret[idx++] = zero ? '0' : '1';
            start = true;
        }
        bit = 0x40000000;
    }
    if (idx == 0)
    {
        ret[idx++] = '0';
    }
    ret[idx] = '\0';
    return ret;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{

    printf("       answer is %s \n", addBinary("1000111111101100010001101101100000011100111001010110000010100111010111000101010001",
                                               "110110101011011101110100000010101111111110011100011011011000110000101010010010010101000110"));
    printf("except answer is %s \n", "110110110100011101100000010100011101011110111001010100101110110011010001101001011010010111");
    printf("            a is     %s \n", "1000111111101100010001101101100000011100111001010110000010100111010111000101010001");
    printf("            b is %s \n", "110110101011011101110100000010101111111110011100011011011000110000101010010010010101000110");
    return 0;
}
