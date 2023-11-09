/*
 * @lc app=leetcode id=5 lang=c
 *
 * [5] Longest Palindromic Substring
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// just O(n^3) while while while!
bool is_palindrome(char *s, int left, int right)
{
    while (left < right)
    {
        /* code */
        if (s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

char *longestPalindrome(char *s)
{
    int length = strlen(s), left = 0, right = length - 1, retLeft = 0, retRight = 0;

    if (length <= 1)
    {
        return s;
    }

    while (left < length)
    {
        while (right > left)
        {
            if (s[left] == s[right])
            {
                // check
                if (is_palindrome(s, left, right) && right - left > retRight - retLeft)
                {
                    retLeft = left;
                    retRight = right;
                }
            }
            right--;
        }
        left++;
        right = length - 1;
    }
    char *ret = malloc(sizeof(char) * (retRight - retLeft + 2));
    strncpy(ret, s + retLeft, retRight - retLeft + 1);
    ret[retRight - retLeft + 1] = '\0';
    return ret;
}

// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{

    char *s = "borcdubqiupahpwjizjjbkncelfazeqynfbrnzuvbhjnyvrlkdyfyjjxnprfocrmisugizsgvhszooktdwhehojbrdbtgkiwkhpfjfcstwcajiuediebdhukqnroxbgtvottummbypokdljjvnthcbesoyigscekrqswdpalnjnhcnqrarxuufzzmkwizptyvjhpfidgmskuaggtpxqisdlyloznkarxofzeeyvteynluofuhbllyiszszbwnsglqjkignusarxsjvctpgiwnhdufmfpanfwxjwlmhgllzsmdpncbwnsbdtsvrjybynifywkulqnzprcxockbhrhvnwxrkvwumyieazclcviumvormynbryaziijpdinwatwqppamfiqfiojgwkvfzyxadyfjrgmtttvlgkqghgbcfhkigfojjkhskzenlpasyozcsuccdxhulcubsgomvcrbqwakrraesfifecmoztayrdjicypakrrneulfbqqxtrdelggedvloebqaztmfyfkhuonrognejxpesmwgnmnnnamvkxqvzrgzdqtvuhccryeowywmbixktnkqnwzlzfvloyqcageugmjqihyjxhssmhkfzxpzxmgpjgsduogfolnkkqizitbvvgrkczmojxnabruwwzxxqcevdwvtiigwckpxnnxxxdhxpgomncttjutrsvyrqcfwxhexhaguddkiesmfrqfjfdaqbkeqinwicphktffuwcazlmerdhraufbpcznbuipmymipxbsdhuesmcwnkdvilqbnkaglloswcpqzdggnhjdkkumfuzihilrpcvemwllicoqiugobhrwdxtoefynqmccamhdtxujfudbglmiwqklriolqfkknbmindxtljulnxhipsieyohnczddabrxzjmompbtnnxvivmoyfzfrxlufowtqzojfclmatthjtbhotdoheusnpirwicbtyrcuojsdmfcx";
    // char *ret = malloc(sizeof(char) * 3);
    // printf("ret is %s", strncpy(ret, s + 0, 3));
    char *ret = longestPalindrome(s);
    printf("ret is %s", ret);

    return 0;
}
