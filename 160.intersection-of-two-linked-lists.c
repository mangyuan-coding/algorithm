/*
 * @lc app=leetcode id=160 lang=c
 *
 * [160] Intersection of Two Linked Lists
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

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    if (headA == NULL || headB == NULL)
    {
        return NULL;
    }

    struct ListNode *tail_A = headA;
    while (tail_A->next != NULL)
    {
        tail_A = tail_A->next;
    }

    tail_A->next = headA;

    struct ListNode *faster = headB, *slower = headB;
    while (1)
    {
        if (faster->next == NULL || faster->next->next == NULL || slower->next == NULL)
        {
            tail_A->next = NULL;
            return NULL;
        }
        faster = faster->next->next;
        slower = slower->next;
        if (faster == slower)
        {
            break;
        }
    }

    faster = headB;

    while (1)
    {
        if (slower == faster)
        {
            break;
        }
        faster = faster->next;
        slower = slower->next;
    }

    tail_A->next = NULL;

    return faster;
}
// @lc code=end
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    struct ListNode *intersection = (struct ListNode *)malloc(sizeof(struct ListNode));
    intersection->val = 8;
    intersection->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    intersection->next->val = 4;
    intersection->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    intersection->next->next->val = 5;
    intersection->next->next->next = NULL;
    struct ListNode *headA = (struct ListNode *)malloc(sizeof(struct ListNode));
    headA->val = 4;
    headA->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    headA->next->val = 1;
    headA->next->next = intersection;
    struct ListNode *headB = (struct ListNode *)malloc(sizeof(struct ListNode));
    headB->val = 5;
    headB->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    headB->next->val = 6;
    headB->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    headB->next->next->val = 1;
    headB->next->next->next = intersection;
    struct ListNode *interse = getIntersectionNode(headA, headB);
    return 0;
}
