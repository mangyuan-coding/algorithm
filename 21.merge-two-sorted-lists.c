/*
 * @lc app=leetcode id=21 lang=c
 *
 * [21] Merge Two Sorted Lists
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

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    if (list1 == NULL || list2 == NULL)
    {
        return list1 == NULL ? list2 : list1;
    }

    struct ListNode *ret = list1->val < list2->val ? list1 : list2, *curret = ret;
    struct ListNode *other = ret == list1 ? list2 : list1;

    while (other != NULL)
    {
        if (curret->next == NULL)
        {
            curret->next = other;
            other = NULL;
        }
        else if (curret->next->val < other->val)
        {
            curret = curret->next;
        }
        else
        {
            struct ListNode *tmp = other;
            other = other->next;
            tmp->next = curret->next;
            curret->next = tmp;
            curret = curret->next;
        }
    }

    return ret;
}
// @lc code=end
