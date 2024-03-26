/*
 * @lc app=leetcode.cn id=143 lang=c
 *
 * [143] Reorder List
 */
#include "include/type.h"

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

void reorderList(struct ListNode *head)
{
    if (head->next == NULL)
    {
        return;
    }
    struct ListNode **nodes = (struct ListNode **)malloc(sizeof(struct ListNode *) * 50000);
    int node_size = 0;

    struct ListNode *node = head;
    do
    {
        node_size++;
        nodes[node_size - 1] = node;
        node = node->next;
    } while (node != NULL);

    for (int i = 0; i < (node_size - 1) / 2; i++)
    {
        struct ListNode *tmp = nodes[i]->next;
        nodes[i]->next = nodes[node_size - i - 1];
        nodes[i]->next->next = tmp;
        nodes[node_size - i - 2]->next = NULL;
    }
}
// @lc code=end
