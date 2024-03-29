/*
 * @lc app=leetcode.cn id=148 lang=c
 *
 * [148] Sort List
 */

#include "include/type.h"
#include <stdio.h>

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdlib.h>

int list_node_cmp(const void *a, const void *b)
{
    return ((*(*(struct ListNode **)a)).val - (*(*(struct ListNode **)b)).val);
}

struct ListNode *sortList(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    struct ListNode **sorted = (struct ListNode **)malloc(sizeof(struct ListNode *) * 50000);
    int sorted_size = 0;
    while (head != NULL)
    {
        sorted[sorted_size++] = head;
        head = head->next;
    }

    qsort(sorted, sorted_size, sizeof(struct ListNode *), list_node_cmp);

    for (int i = 0; i < sorted_size - 1; i++)
    {
        sorted[i]->next = sorted[i + 1];
    }
    sorted[sorted_size - 1]->next = NULL;
    return sorted[0];
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
    // head->next->next->next->next->val = 0;
    // head->next->next->next->next->next = NULL;
    sortList(head);
    return 0;
}
