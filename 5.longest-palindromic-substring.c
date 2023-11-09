/*
 * @lc app=leetcode id=5 lang=c
 *
 * [5] Longest Palindromic Substring
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// optimized dynamic-programming-algorithm
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
char *longestPalindrome(char *s)
{
    int length = strlen(s);
    if (length == 0)
    {
        return NULL;
    }
    if (length == 1)
    {
        return s;
    }

    int cur = 0, distance = 0;
    struct pair ***record = generate(length);

    while (distance < length)
    {
        while (cur < length - distance)
        {
            int rcur = cur + distance;
            if (distance == 0)
            {
                record[cur][rcur] = malloc(sizeof(struct pair));
                record[cur][rcur]->left = cur;
                record[cur][rcur]->right = rcur;
            }
            else if (distance == 1)
            {
                if (s[cur] == s[rcur])
                {
                    record[cur][rcur] = malloc(sizeof(struct pair));
                    record[cur][rcur]->left = cur;
                    record[cur][rcur]->right = rcur;
                }
                else
                {
                    record[cur][rcur] = malloc(sizeof(struct pair));
                    record[cur][rcur]->left = cur;
                    record[cur][rcur]->right = cur;
                }
            }
            else
            {
                struct pair *inner = record[cur + 1][rcur - 1];
                if (s[cur] == s[rcur] && inner->left == cur + 1 && inner->right == rcur - 1)
                {
                    record[cur][rcur] = malloc(sizeof(struct pair));
                    record[cur][rcur]->left = cur;
                    record[cur][rcur]->right = rcur;
                }
                else
                {
                    struct pair *left = record[cur][rcur - 1];
                    struct pair *right = record[cur + 1][rcur];
                    int llen = left->right - left->left;
                    int rlen = right->right - right->left;
                    int ilen = inner->right - inner->left;
                    if (llen >= rlen && llen > ilen)
                    {
                        record[cur][rcur] = left;
                    }
                    else if (rlen > llen && rlen > ilen)
                    {
                        record[cur][rcur] = right;
                    }
                    else
                    {
                        record[cur][rcur] = inner;
                    }
                }
            }
            cur++;
        }
        cur = 0;
        distance++;
    }

    struct pair *ret_pair = record[0][length - 1];
    char *ret = malloc(sizeof(char) * (ret_pair->right - ret_pair->left + 2));
    strncpy(ret, s + ret_pair->left, ret_pair->right - ret_pair->left + 1);
    ret[ret_pair->right - ret_pair->left + 1] = '\0';
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
