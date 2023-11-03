/*
 * @lc app=leetcode id=2 lang=c
 *
 * [2] Add Two Numbers
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
#include <stdbool.h>

const size_t NODE_SIZE = sizeof(struct ListNode);

struct ListNode *build(int *val, int length)
{
    struct ListNode *head = malloc(NODE_SIZE), *node = head;
    node->val = val[0];
    node->next = NULL;

    for (int i = 1; i < length; i++)
    {
        node->next = malloc(NODE_SIZE);
        node = node->next;
        node->val = val[i];
        node->next = NULL;
    }
    return head;
}

int listSize(struct ListNode *node)
{
    int ret = 0;
    while (node != NULL)
    {
        ret++;
        node = node->next;
    }
    return ret;
}

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

    int l1Size = listSize(l1);
    int l2Size = listSize(l2);

    int tmp = 0;
    struct ListNode *longer = l1Size >= l2Size ? l1 : l2;
    struct ListNode *shorter = l1Size < l2Size ? l1 : l2;
    struct ListNode *ret = longer;

    do
    {
        int val = longer->val + tmp;
        tmp = 0;
        if (shorter != NULL)
        {
            val += shorter->val;
            shorter = shorter->next;
        }

        int quotient = val / 10;
        if (quotient > 0)
        {
            tmp = quotient;
            longer->val = val % 10;
        }
        else
        {
            longer->val = val;
        }

        if (longer->next == NULL && tmp > 0)
        {
            longer->next = malloc(NODE_SIZE);
            longer->next->next = NULL;
            longer->next->val = 0;
        }

        longer = longer->next;

    } while (longer != NULL);

    return ret;
}
// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{

    // test-case
    // [2,4,3]
    // [5,6,4]
    int l1Nums[] = {2, 4, 3};
    struct ListNode *l1 = build(l1Nums, 3);
    int l2Nums[] = {5, 6, 4};
    struct ListNode *l2 = build(l2Nums, 3);

    struct ListNode *ret = addTwoNumbers(l1, l2);

    while (ret != NULL)
    {
        printf("%d\n", ret->val);
        ret = ret->next;
    }

    return 0;
}
