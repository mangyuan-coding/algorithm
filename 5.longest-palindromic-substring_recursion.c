/*
 * @lc app=leetcode id=5 lang=c
 *
 * [5] Longest Palindromic Substring
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// recursion, but fault!!, time limit O(n^2 * logn)
struct pair
{
    int left;
    int right;
};

struct pair ***generate(int length)
{
    struct pair **ret_one = malloc(sizeof(struct pair) * length);
    for (int i = 0; i < length; i++)
    {
        ret_one[i] = NULL;
    }
    struct pair ***ret = malloc(sizeof(ret_one) * length);
    ret[0] = ret_one;
    for (int i = 1; i < length; i++)
    {
        ret[i] = malloc(sizeof(struct pair) * length);
        for (int j = 0; j < length; j++)
        {
            ret[i][j] = NULL;
        }
    }
    return ret;
}

struct pair *longestPalindrome_recursion(char *s, struct pair ***record, int left, int right)
{
    if (record[left][right] != NULL)
    {
        return record[left][right];
    }

    record[left][right] = malloc(sizeof(struct pair));

    if (left == right)
    {

        record[left][right]->left = left;
        record[left][right]->right = right;
        return record[left][right];
    }

    if (left + 1 == right)
    {
        if (s[left] == s[right])
        {
            record[left][right]->left = left;
            record[left][right]->right = right;
        }
        else
        {
            record[left][right]->left = left;
            record[left][right]->right = left;
        }
        return record[left][right];
    }

    struct pair *next = longestPalindrome_recursion(s, record, left + 1, right - 1);
    if (s[left] == s[right] && next->left == left + 1 && next->right == right - 1)
    {
        record[left][right]->left = left;
        record[left][right]->right = right;
    }
    else
    {
        struct pair *leftPalindrome = longestPalindrome_recursion(s, record, left, right - 1);
        struct pair *rightPalindrome = longestPalindrome_recursion(s, record, left + 1, right);

        int nextLen = next->right - next->left;
        int leftLen = leftPalindrome->right - leftPalindrome->left;
        int rightLen = rightPalindrome->right - rightPalindrome->left;
        if (leftLen >= rightLen && leftLen > nextLen)
        {
            record[left][right] = leftPalindrome;
        }
        else if (rightLen > leftLen && rightLen > nextLen)
        {
            record[left][right] = rightPalindrome;
        }
        else
        {
            record[left][right] = next;
        }
    }
    return record[left][right];
}

char *longestPalindrome(char *s)
{
    int length = strlen(s);
    struct pair ***record = generate(length);
    struct pair *retPair = longestPalindrome_recursion(s, record, 0, length - 1);
    char *ret = malloc(sizeof(char) * (retPair->right - retPair->left + 2));
    strncpy(ret, s + retPair->left, retPair->right - retPair->left + 1);
    ret[retPair->right - retPair->left + 1] = '\0';
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
