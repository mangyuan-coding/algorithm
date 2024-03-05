/*
 * @lc app=leetcode id=92 lang=c
 *
 * [92] Reverse Linked List II
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
#include <stdbool.h>

struct ListNode *reverseBetween(struct ListNode *head, int left, int right)
{
    if (head->next == NULL)
    {
        return head;
    }

    if (left == right)
    {
        return head;
    }

    struct ListNode *left_pre = NULL, *right_next = NULL, *reversed = NULL, *reversed_tail = NULL;

    struct ListNode *pointer = head, *pointer_pre = NULL;
    int idx = 1;
    if (left != 1)
    {
        for (; idx < left - 1; idx++)
        {
            pointer = pointer->next;
        }
        left_pre = pointer;
        pointer_pre = pointer;
        pointer = pointer->next;
        idx++;
    }
    for (; idx <= right; idx++)
    {
        pointer_pre = pointer;
        pointer = pointer->next;
        pointer_pre->next = reversed;
        reversed = pointer_pre;
        if (reversed_tail == NULL)
        {
            reversed_tail = reversed;
        }
    }
    reversed_tail->next = pointer;
    if (left_pre == NULL)
    {
        return reversed;
    }
    left_pre->next = reversed;
    return head;
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
    struct ListNode *reversed = reverseBetween(head, 2, 4);
    while (reversed != NULL)
    {
        printf("%d ", reversed->val);
        reversed = reversed->next;
    }
    return 0;
}
