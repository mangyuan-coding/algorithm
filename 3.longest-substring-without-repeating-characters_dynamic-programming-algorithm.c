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

// dynamic programming algorithm
// f(i) = f(i - 1) contains x(i - 1) ? x(i - 1) == x(i) ? f(i - 1) : f(i - 1) concat x(i) : MaxLength(f(i - 1), x(j) ~ x(i));
int lengthOfLongestSubstring(char *s)
{
    int left = 0, right = 0, length = strlen(s);

    if (length == 0)
    {
        return 0;
    }

    struct node *nodes = NULL, *tmpNodes = NULL;
    nodes = insert(nodes, s[0] - '0', 0);

    for (int i = 1; i < length; i++)
    {
        /* code */
        if (right + 1 == i)
        {
            if (contains(nodes, s[i] - '0'))
            {
                continue;
            }
            else
            {
                nodes = insert(nodes, s[i] - '0', i);
                right++;
            }
        }
        else
        {
            int curLeft = i;
            tmpNodes = insert(tmpNodes, s[i] - '0', i);
            for (int j = i - 1; i >= 0; j--)
            {
                /* code */
                if (contains(tmpNodes, s[j] - '0'))
                {
                    curLeft = j + 1;
                    break;
                }
                else
                {
                    tmpNodes = insert(tmpNodes, s[j] - '0', j);
                }
            }
            if (i - curLeft > right - left)
            {
                left = curLeft;
                right = i;
                delete_all(nodes);
                nodes = tmpNodes;
                tmpNodes = NULL;
            }
            else
            {
                delete_all(tmpNodes);
                tmpNodes = NULL;
            }
        }
    }

    return right - left + 1;
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
