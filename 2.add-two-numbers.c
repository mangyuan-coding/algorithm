/*
 * @lc app=leetcode id=2 lang=c
 *
 * [2] Add Two Numbers
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdbool.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    if (l1 == NULL)
    {
        return l2;
    }
    if (l2 == NULL)
    {
        return l1;
    }

    int tmp = 0;
    struct ListNode *head = malloc(sizeof(struct ListNode)), *node = head;

    do
    {
        /* code */
        int val = l1->val + l2->val;
        if (tmp != 0)
        {
            val += tmp;
        }
        if (val / 10 > 0)
        {
            tmp = val / 10;
        }
        val = val % 10;

        // next step
        node->next = l1;
        l1 = l1->next;
        l2 = l2->next;
    } while (l1 == NULL && l2 == NULL && tmp == 0);
}
// @lc code=end
