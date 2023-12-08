/*
 * @lc app=leetcode id=24 lang=c
 *
 * [24] Swap Nodes in Pairs
 */
struct ListNode
{
    int val;
    struct ListNode *next;
};
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdlib.h>

struct ListNode *swapPairs(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    struct ListNode *current = head;
    struct ListNode *pre = NULL;
    while (current != NULL && current->next != NULL)
    {
        struct ListNode *next = current->next;

        current->next = next->next;
        next->next = current;
        if (current == head)
        {
            head = next;
        }
        if (pre != NULL)
        {
            pre->next = next;
        }

        pre = current;
        current = current->next;
    }
    return head;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct ListNode *head = malloc(sizeof(struct ListNode) * 4);
    head->val = 1;
    head->next = &head[1];
    head[1].val = 2;
    head[1].next = &head[2];
    head[2].val = 3;
    head[2].next = &head[3];
    head[3].val = 4;
    head[3].next = NULL;

    head = swapPairs(head);
    while (head != NULL)
    {
        printf("head value is %d \n", head->val);
        head = head->next;
    }

    return 0;
}
