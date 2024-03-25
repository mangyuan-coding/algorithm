/*
 * @lc app=leetcode.cn id=138 lang=c
 *
 * [138] Copy List with Random Pointer
 */
#include "uthash/src/uthash.h"
#include <stdio.h>

struct Node
{
    int val;
    struct Node *next;
    struct Node *random;
};

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */
#include <stdlib.h>

typedef struct map_node
{
    struct Node *key;
    struct Node *val;
    UT_hash_handle hh;
} map_node;

map_node *map_nodes = NULL;

struct Node *deep_clone(struct Node *head)
{

    struct Node *cloned = (struct Node *)malloc(sizeof(struct Node));
    cloned->val = head->val;

    struct map_node *map_node = (struct map_node *)malloc(sizeof(struct map_node));
    map_node->key = head;
    map_node->val = cloned;

    HASH_ADD_PTR(map_nodes, key, map_node);

    if (head->next != NULL)
    {
        cloned->next = deep_clone(head->next);
    }
    else
    {
        cloned->next = NULL;
    }
    return cloned;
}

void connect(struct Node *cloned, struct Node *copyed)
{
    if (copyed->random != NULL)
    {
        struct map_node *map_node;
        HASH_FIND_PTR(map_nodes, &(copyed->random), map_node);
        cloned->random = map_node->val;
    }
    else
    {
        cloned->random = NULL;
    }
    if (copyed->next != NULL)
    {
        connect(cloned->next, copyed->next);
    }
}

void delete_all()
{
    struct map_node *cur_node;
    struct map_node *tmp;

    HASH_ITER(hh, map_nodes, cur_node, tmp)
    {
        HASH_DEL(map_nodes, cur_node); /* delete it (users advances to next) */
        free(cur_node);                /* free it */
    }
}

struct Node *copyRandomList(struct Node *head)
{
    if (head == NULL)
    {
        return head;
    }
    delete_all();
    free(map_nodes);
    struct Node *cloned = deep_clone(head);
    connect(cloned, head);
    return cloned;
}
// @lc code=end
