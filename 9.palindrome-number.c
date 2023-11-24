/*
 * @lc app=leetcode id=9 lang=c
 *
 * [9] Palindrome Number
 */

// @lc code=start
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool isPalindrome(int x)
{
    if (x < 0)
    {
        return false;
    }
    if (x < 10)
    {
        return true;
    }

    char array[10] = "\0";

    int l = 9;

    while (x >= 10)
    {
        /* code */
        array[l--] = (x % 10) + '0';
        x = x / 10;
    }

    array[l] = x + '0';

    int r = 9;
    while (l < r)
    {
        if (array[l] != array[r])
        {
            return false;
        }
        l++;
        r--;
    }

    return true;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("isPalindrome %d", isPalindrome(1240421));
    return 0;
}
