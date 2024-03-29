/*
 * @lc app=leetcode.cn id=147 lang=c
 *
 * [147] Insertion Sort List
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
#include <stdlib.h>

typedef struct double_link
{
    struct ListNode *node;
    struct double_link *pre;
    struct double_link *next;
} double_link;

struct ListNode *insertionSortList(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct double_link *d_tail = NULL, *finding;

    while (head != NULL)
    {
        if (d_tail == NULL)
        {
            d_tail = (struct double_link *)malloc(sizeof(struct double_link));
            d_tail->node = head;
            d_tail->pre = NULL;
            d_tail->next = NULL;
        }
        else
        {
            finding = d_tail;
            while (finding->pre != NULL)
            {
                if (finding->node->val < head->val)
                {
                    break;
                }
                finding = finding->pre;
            }

            struct double_link *new_link = (struct double_link *)malloc(sizeof(struct double_link));
            new_link->node = head;
            new_link->next = NULL;
            new_link->pre = NULL;

            if (finding->node->val > head->val)
            {
                new_link->next = finding;
                new_link->pre = finding->pre;
                if (finding->pre != NULL)
                {
                    finding->pre->next = new_link;
                }
                finding->pre = new_link;
            }
            else
            {
                new_link->next = finding->next;
                if (finding->next != NULL)
                {
                    finding->next->pre = new_link;
                }
                new_link->pre = finding;
                finding->next = new_link;
            }
            if (d_tail->next != NULL)
            {
                d_tail = d_tail->next;
            }
        }
        head = head->next;
    }

    d_tail->node->next = NULL;

    while (d_tail->pre != NULL)
    {
        d_tail->pre->node->next = d_tail->node;
        d_tail = d_tail->pre;
    }

    return d_tail->node;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->val = 4;
    head->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->val = 1;
    head->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->val = 3;
    head->next->next->next->next = NULL;
    insertionSortList(head);
    return 0;
}
