/*
 * @lc app=leetcode id=141 lang=c
 *
 * [141] Linked List Cycle
 */
#include <stdbool.h>
#include "include/type.h"

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

bool hasCycle(struct ListNode *head)
{
    if (head == NULL || head->next == NULL || head->next->next == NULL)
    {
        return false;
    }

    struct ListNode *slower = head->next, *faster = head->next->next;

    while (1)
    {
        if (slower->next == NULL || faster->next == NULL || faster->next->next == NULL)
        {
            return false;
        }
        if (slower == faster)
        {
            return true;
        }
        slower = slower->next;
        faster = faster->next->next;
    }

    return true;
}
// @lc code=end
