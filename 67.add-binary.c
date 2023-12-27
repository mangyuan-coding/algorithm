/*
 * @lc app=leetcode id=67 lang=c
 *
 * [67] Add Binary
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const unsigned long long mask = 0x8000000000000000;

char *addBinary(char *a, char *b)
{
    int len_a = strlen(a);
    int len_b = strlen(b);

    // 10000 / 63 = 158.73
    // 159
    // 64 * 159 = 10176
    int bit_size_base = ((fmax(len_a, len_b) + 1) / 63) + 1;
    unsigned long long *bit_a = (unsigned long long *)malloc(sizeof(unsigned long long *) * bit_size_base);
    unsigned long long *bit_b = (unsigned long long *)malloc(sizeof(unsigned long long *) * bit_size_base);
    unsigned long long *bit_c = (unsigned long long *)malloc(sizeof(unsigned long long *) * bit_size_base);
    for (int i = 0; i < bit_size_base; i++)
    {
        bit_a[i] = 0x0;
        bit_b[i] = 0x0;
        bit_c[i] = 0x0;
    }

    for (int i = 0; i < len_a; i++)
    {
        int idx = i / 63;
        bit_a[bit_size_base - idx - 1] <<= 1;
        bit_a[bit_size_base - idx - 1] += a[i] - '0';
    }

    for (int i = 0; i < len_b; i++)
    {
        int idx = i / 63;
        bit_b[bit_size_base - idx - 1] <<= 1;
        bit_b[bit_size_base - idx - 1] += b[i] - '0';
    }

    int ret_size = 0;
    int carry = 0x0;

    for (int i = bit_size_base - 1; i >= 0; i--)
    {
        printf("bit_a[%d] is 0x%llx \n", i, bit_a[i]);
        printf("bit_b[%d] is 0x%llx \n", i, bit_b[i]);
        bit_c[i] = bit_a[i] + bit_b[i] + carry;
        carry = mask & bit_c[i] > 0 ? 0x1 : 0x0;
        printf("bit_c[%d] is 0x%llx \n", i, bit_c[i]);
    }

    char *ret = (char *)malloc(sizeof(char) * (fmax(len_a, len_b) + 2));
    int idx = 0;

    for (int i = 0; i < bit_size_base; i++)
    {
        if (idx == 0 && bit_c[i] == 0)
        {
            continue;
        }
        bit_c[i] <<= 1;

        bool start = false;
        for (int j = 1; j < 64; j++)
        {
            bit_c[i] <<= 1;
            bool zero = (mask & bit_c[i]) == 0;
            if (zero && !start && idx == 0)
            {
                continue;
            }
            ret[idx++] = zero ? '0' : '1';
            start = true;
        }
    }
    if (idx == 0)
    {
        ret[idx++] = '0';
    }
    ret[idx] = '\0';
    return ret;
}
// @lc code=end

int main(int argc, char const *argv[])
{

    printf("       answer is %s \n", addBinary("10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101", "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011"));
    printf("except answer is %s \n", "110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000");
    printf("            a is     %s \n", "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101");
    printf("            b is %s \n", "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011");
    return 0;
}
