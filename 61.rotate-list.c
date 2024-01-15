/*
 * @lc app=leetcode id=61 lang=c
 *
 * [61] Rotate List
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
struct ListNode *rotateRight(struct ListNode *head, int k)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    int size = 1;
    struct ListNode *cur = head;
    while (cur->next != NULL)
    {
        size++;
        cur = cur->next;
    }
    if (k >= size)
    {
        k = k % size;
    }
    if (k == 0)
    {
        return head;
    }
    cur->next = head;

    k = size - k;
    for (int i = 0; i < k; i++)
    {
        cur = cur->next;
    }

    struct ListNode *new_head = cur->next;
    cur->next = NULL;

    return new_head;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->val = 3;
    head->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->val = 4;
    head->next->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->next->val = 5;
    head->next->next->next->next->next = NULL;

    struct ListNode *ret = rotateRight(head, 2);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", ret->val);
        ret = ret->next;
    }

    return 0;
}
