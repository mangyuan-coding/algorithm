/*
 * @lc app=leetcode id=82 lang=c
 *
 * [82] Remove Duplicates from Sorted List II
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

struct ListNode *deleteDuplicates(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct ListNode *first_distinct_node = NULL,
                    *last_distinct_node = NULL,
                    *cur_node = head;
    bool same_node = false;
    while (cur_node != NULL)
    {
        if (cur_node->next == NULL)
        {
            if (!same_node)
            {
                if (last_distinct_node == NULL)
                {
                    first_distinct_node = cur_node;
                    last_distinct_node = cur_node;
                }
                else
                {
                    last_distinct_node->next = cur_node;
                    last_distinct_node = last_distinct_node->next;
                }
            }
            if (last_distinct_node != NULL)
            {
                last_distinct_node->next = NULL;
            }
            break;
        }
        else if (cur_node->val == cur_node->next->val)
        {
            cur_node = cur_node->next;
            same_node = true;
        }
        else
        {
            if (!same_node)
            {
                if (last_distinct_node == NULL)
                {
                    first_distinct_node = cur_node;
                    last_distinct_node = cur_node;
                }
                else
                {
                    last_distinct_node->next = cur_node;
                    last_distinct_node = last_distinct_node->next;
                }
            }
            cur_node = cur_node->next;
            same_node = false;
        }
    }
    return first_distinct_node;
}
// @lc code=end
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->val = 2;
    head->next->next->next = NULL;
    // head->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    // head->next->next->next->val = 3;
    // head->next->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    // head->next->next->next->next->val = 4;
    // head->next->next->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    // head->next->next->next->next->next->val = 4;
    // head->next->next->next->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    // head->next->next->next->next->next->next->val = 5;
    // head->next->next->next->next->next->next->next = NULL;

    head = deleteDuplicates(head);
    return 0;
}
