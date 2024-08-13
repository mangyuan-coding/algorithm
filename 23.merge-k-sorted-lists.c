/*
 * @lc app=leetcode.cn id=23 lang=c
 *
 * [23] Merge k Sorted Lists
 *
 * https://leetcode.cn/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (60.10%)
 * Likes:    2862
 * Dislikes: 0
 * Total Accepted:    845.4K
 * Total Submissions: 1.4M
 * Testcase Example:  '[[1,4,5],[1,3,4],[2,6]]'
 *
 * You are given an array of k linked-lists lists, each linked-list is sorted
 * in ascending order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 *
 * Example 1:
 *
 *
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * Explanation: The linked-lists are:
 * [
 * ⁠ 1->4->5,
 * ⁠ 1->3->4,
 * ⁠ 2->6
 * ]
 * merging them into one sorted list:
 * 1->1->2->3->4->4->5->6
 *
 *
 * Example 2:
 *
 *
 * Input: lists = []
 * Output: []
 *
 *
 * Example 3:
 *
 *
 * Input: lists = [[]]
 * Output: []
 *
 *
 *
 * Constraints:
 *
 *
 * k == lists.length
 * 0 <= k <= 10^4
 * 0 <= lists[i].length <= 500
 * -10^4 <= lists[i][j] <= 10^4
 * lists[i] is sorted in ascending order.
 * The sum of lists[i].length will not exceed 10^4.
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/type.h"

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0 || (listsSize == 1 && lists[0] == NULL))
    {
        return NULL;
    }
    struct ListNode **value_map = (struct ListNode **)malloc(sizeof(struct ListNode *) * 20000);
    for (int i = 0; i < 20000; i++)
    {
        value_map[i] = NULL;
    }

    struct ListNode *current, *next, *idx_current;
    int idx;
    for (int i = 0; i < listsSize; i++)
    {
        current = lists[i];
        next = NULL;
        while (current != NULL)
        {
            if (current->next != NULL)
            {
                next = current->next;
            }

            idx = current->val + 9999;
            if (value_map[idx] == NULL)
            {
                value_map[idx] = current;
            }
            else
            {
                idx_current = value_map[idx];
                while (idx_current->next != NULL)
                {
                    idx_current = idx_current->next;
                }
                idx_current->next = current;
            }
            current->next = NULL;
            current = next;
            next = NULL;
        }
    }

    struct ListNode *head = NULL, *pre;
    for (int i = 0; i < 20000; i++)
    {
        if (value_map[i] != NULL)
        {
            if (head == NULL)
            {
                head = value_map[i];
                pre = head;
            }
            else
            {
                pre->next = value_map[i];
            }
            while (pre->next != NULL)
            {
                pre = pre->next;
            }
        }
    }
    return head;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int listsSize = 3;
    struct ListNode **lists = (struct ListNode **)malloc(sizeof(struct ListNode *) * listsSize);
    lists[0] = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[0]->val = 1;
    lists[0]->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[0]->next->val = 4;
    lists[0]->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[0]->next->next->val = 5;
    lists[0]->next->next->next = NULL;
    lists[1] = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[1]->val = 1;
    lists[1]->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[1]->next->val = 3;
    lists[1]->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[1]->next->next->val = 4;
    lists[1]->next->next->next = NULL;
    lists[2] = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[2]->val = 2;
    lists[2]->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    lists[2]->next->val = 6;
    lists[2]->next->next = NULL;
    mergeKLists(lists, listsSize);
    return 0;
}
