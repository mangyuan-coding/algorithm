/*
 * @lc app=leetcode id=3 lang=c
 *
 * [3] Longest Substring Without Repeating Characters
 */

#include "uthash/src/uthash.h"

// @lc code=start
#include <stdbool.h>
#include <string.h>

struct node
{
    int key;
    int index;
    UT_hash_handle hh;
};

struct node *find(struct node *nodes, int key)
{
    struct node *tmp;
    HASH_FIND_INT(nodes, &key, tmp);
    return tmp;
}

struct node *insert(struct node *nodes, int key, int index)
{
    struct node *it = find(nodes, key);
    if (it == NULL)
    {
        struct node *tmp = malloc(sizeof(struct node));
        tmp->key = key, tmp->index = index;
        HASH_ADD_INT(nodes, key, tmp);
        return nodes;
    }
    else
    {
        it->index = index;
        return nodes;
    }
}

bool contains(struct node *nodes, int key)
{
    return find(nodes, key) != NULL;
}

void delete_all(struct node *nodes)
{
    struct node *current_node, *tmp;

    HASH_ITER(hh, nodes, current_node, tmp)
    {
        HASH_DEL(nodes, current_node);
        free(current_node);
    }
}

// sliding window
// define f(i, j) is substring of s as i is the first charset
// f(i + 1, j + n) is substring of s as i + 1 is the first charset
// compare f(i, j) and f(i + 1, j + n), same substring s[i + 1, j]

struct node *delete(struct node *nodes, int key)
{
    struct node *current_node, *tmp;

    HASH_ITER(hh, nodes, current_node, tmp)
    {
        if (current_node->key == key)
        {
            HASH_DEL(nodes, current_node);
            free(current_node);
            break;
        }
    }
    return nodes;
}

#include <math.h>

int lengthOfLongestSubstring(char *s)
{
    int length = strlen(s);
    if (length <= 0)
    {
        return 0;
    }

    int left = 0, right = 0, maxLen = 0;
    struct node *nodes = NULL;

    while (right < length)
    {
        /* code */
        struct node *existed = find(nodes, s[right] - '0');
        if (existed == NULL)
        {
            nodes = insert(nodes, s[right] - '0', right);
            maxLen = fmax(maxLen, right - left + 1);
        }
        else
        {
            int new_left = existed->index + 1;
            while (left < new_left)
            {
                nodes = delete (nodes, s[left] - '0');
                left++;
            }
            nodes = insert(nodes, s[right] - '0', right);
        }
        right++;
    }
    return maxLen;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{
    char s[] = "abcabcbb";
    int length = lengthOfLongestSubstring(s);
    printf("length of longest substring is %d", length);
    return 0;
}
