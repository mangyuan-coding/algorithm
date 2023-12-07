/*
 * @lc app=leetcode id=19 lang=c
 *
 * [19] Remove Nth Node From End of List
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

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    if (head == NULL)
    {
        return head;
    }

    int len = 0;
    struct ListNode *current = head;
    while (current != NULL)
    {
        len++;
        current = current->next;
    }

    if (len == 1)
    {
        return NULL;
    }

    if (len == n)
    {
        return head->next;
    }

    current = head;
    for (int i = 1; i < len - n; i++)
    {
        current = current->next;
    }

    struct ListNode *removed = current->next;
    current->next = current->next->next;
    removed->next = NULL;

    return head;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode) * 2);
    head[0].val = 1;
    head[0].next = &head[1];
    head[1].val = 2;
    head[1].next = NULL;

    struct ListNode *ret = removeNthFromEnd(head, 2);
    while (ret != NULL)
    {
        printf("ret is %d \n", ret->val);
        ret = ret->next;
    }

    return 0;
}
