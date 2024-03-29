/*
 * @lc app=leetcode.cn id=146 lang=c
 *
 * [146] LRU Cache
 */

#include <stdio.h>

// @lc code=start
#include <stdlib.h>

typedef struct entry
{
    int key;
    int hash;
    int value;
    struct entry *parent;
    struct entry *child;
    struct entry *pre;
    struct entry *next;
} entry;

typedef struct LRUCache
{
    int size;
    int capacity;
    struct entry *head;
    struct entry *tail;
    struct entry **table;
} LRUCache;

int hashing(int key)
{
    return key ^ (key >> 16);
}

void after_access(struct LRUCache *obj, struct entry *node)
{
    // nothing
    if (obj->head == NULL)
    {
        obj->head = node;
        obj->tail = node;
    }
    else if (obj->head != node)
    {
        if (node->pre == NULL && node->next == NULL)
        {
            obj->head->pre = node;
            node->next = obj->head;
            obj->head = node;
        }
        else
        {
            if (obj->tail == node)
            {
                node->pre->next = NULL;
                obj->tail = node->pre;
            }
            else
            {
                node->pre->next = node->next;
                node->next->pre = node->pre;
            }
            node->pre = NULL;
            node->next = obj->head;
            obj->head->pre = node;
            obj->head = node;
        }
    }
}

void after_removal(struct LRUCache *obj, struct entry *node)
{
    if (node == obj->head && node == obj->tail)
    {
        obj->head = NULL;
        obj->tail = NULL;
    }
    else if (node == obj->head)
    {
        obj->head = node->next;
        obj->head->pre = NULL;
    }
    else if (node == obj->tail)
    {
        obj->tail = node->pre;
        obj->tail->next = NULL;
    }
    else
    {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    node->pre = NULL;
    node->next = NULL;
    free(node);
}

struct entry *find_node(struct LRUCache *obj, int key)
{
    int hash = hashing(key);
    int idx = (obj->capacity - 1) & hash;
    if (obj->table[idx] == NULL)
    {
        return NULL;
    }
    struct entry *node = obj->table[idx];
    while (node != NULL && node->key != key)
    {
        node = node->child;
    }
    return node;
}

struct LRUCache *lRUCacheCreate(int capacity)
{
    struct LRUCache *cache = (struct LRUCache *)malloc(sizeof(struct LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->table = (struct entry **)malloc(sizeof(struct entry *) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        cache->table[i] = NULL;
    }
    return cache;
}

int lRUCacheGet(struct LRUCache *obj, int key)
{
    entry *node = find_node(obj, key);
    if (node == NULL)
    {
        return -1;
    }
    after_access(obj, node);
    return node->value;
}

void lRUCachePut(struct LRUCache *obj, int key, int value)
{
    struct entry *node = find_node(obj, key);
    if (node != NULL)
    {
        node->value = value;
    }
    else
    {
        node = (struct entry *)malloc(sizeof(struct entry));
        node->key = key;
        node->value = value;
        node->parent = NULL;
        node->child = NULL;
        node->pre = NULL;
        node->next = NULL;

        int hash = hashing(key);
        node->hash = hash;
        int idx = (obj->capacity - 1) & hash;
        if (obj->table[idx] != NULL)
        {
            struct entry *parent = obj->table[idx];
            while (parent->child != NULL)
            {
                parent = parent->child;
            }
            parent->child = node;
            node->parent = parent;
        }
        else
        {
            obj->table[idx] = node;
        }
        obj->size++;
        if (obj->size == obj->capacity + 1)
        {
            struct entry *removed = obj->tail;
            if (removed->parent != NULL)
            {
                removed->parent->child = removed->child;
            }
            else
            {
                int removed_idx = (obj->capacity - 1) & removed->hash;
                if (removed->child != NULL)
                {
                    obj->table[removed_idx] = removed->child;
                }
                else
                {
                    obj->table[removed_idx] = NULL;
                }
            }
            if (removed->child != NULL)
            {
                removed->child->parent = removed->parent;
            }
            removed->child = NULL;
            removed->parent = NULL;
            obj->size--;
            after_removal(obj, removed);
        }
    }
    after_access(obj, node);
}

void lRUCacheFree(struct LRUCache *obj)
{
    if (obj->size > 0)
    {
        struct entry *node = obj->tail;
        while (node->pre != NULL)
        {
            node = node->pre;
            free(node->next);
        }
        free(obj->table);
    }
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/
// @lc code=end
int main(int argc, char const *argv[])
{
    int value = 0;
    struct LRUCache *cache = lRUCacheCreate(3);
    lRUCachePut(cache, 1, 1);
    lRUCachePut(cache, 2, 2);
    lRUCachePut(cache, 3, 3);
    lRUCachePut(cache, 4, 4);
    value = lRUCacheGet(cache, 4);
    value = lRUCacheGet(cache, 3);
    value = lRUCacheGet(cache, 2);
    value = lRUCacheGet(cache, 1);
    lRUCachePut(cache, 5, 5);
    value = lRUCacheGet(cache, 1);
    value = lRUCacheGet(cache, 2);
    value = lRUCacheGet(cache, 3);
    value = lRUCacheGet(cache, 4);
    value = lRUCacheGet(cache, 5);
    lRUCacheFree(cache);
    return 0;
}
