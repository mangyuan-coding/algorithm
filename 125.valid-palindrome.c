/*
 * @lc app=leetcode id=125 lang=c
 *
 * [125] Valid Palindrome
 */

#include <stdbool.h>

// @lc code=start
#include <string.h>
#include <math.h>

bool isPalindrome(char *s)
{
    int len = strlen(s);
    if (len == 1)
    {
        return true;
    }

    int left = 0, right = len - 1;
    while (left <= right)
    {
        if (s[left] < '0' || (s[left] > '9' && s[left] < 'A') || (s[left] > 'Z' && s[left] < 'a') || s[left] > 'z')
        {
            left++;
        }
        else if (s[right] < '0' || (s[right] > '9' && s[right] < 'A') || (s[right] > 'Z' && s[right] < 'a') || s[right] > 'z')
        {
            right--;
        }
        else
        {
            if ((s[left] <= '9' || s[right] <= '9') && s[left] != s[right])
            {
                return false;
            }
            int a = 0;
            if (s[left] < 'a')
            {
                a = s[left] - 'A';
            }
            else
            {
                a = s[left] - 'a';
            }
            int b = 0;
            if (s[right] < 'a')
            {
                b = s[right] - 'A';
            }
            else
            {
                b = s[right] - 'a';
            }
            if (a != b)
            {
                return false;
            }
            left++;
            right--;
        }
    }

    return true;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf(" %d ", 'A');
    printf(" %d ", 'Z');
    printf(" %d ", 'a');
    printf(" %d ", 'z');
    char *s = "A man, a plan, a canal: Panama";
    printf("%d ", isPalindrome(s));
    return 0;
}
