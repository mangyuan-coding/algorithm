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

    struct ListNode *x_node = head, *pre_x_node = NULL;
    while (x_node != NULL && x_node->val != x)
    {
        pre_x_node = x_node;
        x_node = x_node->next;
    }
    if (x_node == NULL || x_node->next == NULL)
    {
        return head;
    }

    struct ListNode *left, *right = x_node;
    while (right->next != NULL)
    {
        if (right->next->val < x)
        {
            if (x_node == head)
            {
                left = right->next;
                right = right->next->next;
                left->next = x_node;
                head = left;
            }
            else
            {
                left = head;
                while (left != x_node)
                {
                       
                }
            }
        }
        else
        {
            right = right->next;
        }
    }
    return head;
}
// @lc code=end
