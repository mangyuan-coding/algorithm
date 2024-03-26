/*
 * @lc app=leetcode.cn id=142 lang=c
 *
 * [142] Linked List Cycle II
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
struct ListNode *detectCycle(struct ListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    struct ListNode *slower = head, *faster = head;

    do
    {
        if (slower->next == NULL || faster->next == NULL || faster->next->next == NULL)
        {
            return NULL;
        }
        slower = slower->next;
        faster = faster->next->next;
    } while (slower != faster);

    struct ListNode *same_one = head, *same_two = slower;
    while (same_two != same_one)
    {
        same_one = same_one->next;
        same_two = same_two->next;
    }
    return same_one;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->val = 3;
    head->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->val = 0;
    head->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->val = -4;
    head->next->next->next->next = head->next;
    detectCycle(head);
    return 0;
}
