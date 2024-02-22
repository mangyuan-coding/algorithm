/*
 * @lc app=leetcode id=86 lang=c
 *
 * [86] Partition List
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
struct ListNode *partition(struct ListNode *head, int x)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct ListNode *cur = head,
                    *smaller_first = NULL, *smaller_last = NULL,
                    *greater_fist = NULL, *greater_last = NULL;

    while (cur != NULL)
    {
        if (cur->val < x)
        {
            if (smaller_first == NULL)
            {
                smaller_last = cur;
                smaller_first = smaller_last;
            }
            else
            {
                smaller_last->next = cur;
                smaller_last = smaller_last->next;
            }
        }
        else
        {
            if (greater_fist == NULL)
            {
                greater_fist = cur;
                greater_last = cur;
            }
            else
            {
                greater_last->next = cur;
                greater_last = greater_last->next;
            }
        }
        cur = cur->next;
    }

    if (smaller_first == NULL)
    {
        smaller_first = head;
    }
    else
    {
        smaller_last->next = greater_fist;
    }
    if (greater_last != NULL)
    {
        greater_last->next = NULL;
    }

    return smaller_first;
}
// @lc code=end
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // 4,2,2,3,5
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->val = 4;
    head->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->val = 3;
    head->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->val = 2;
    head->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->val = 5;
    head->next->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->next->val = 2;
    head->next->next->next->next->next = NULL;
    partition(head, 3);
    return 0;
}
