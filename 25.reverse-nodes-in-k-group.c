/*
 * @lc app=leetcode.cn id=25 lang=c
 *
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (68.30%)
 * Likes:    2374
 * Dislikes: 0
 * Total Accepted:    641.4K
 * Total Submissions: 939.2K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list.
 *
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes, in the end, should remain as it is.
 *
 * You may not alter the values in the list's nodes, only nodes themselves may
 * be changed.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,2,3,4,5], k = 3
 * Output: [3,2,1,4,5]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is n.
 * 1 <= k <= n <= 5000
 * 0 <= Node.val <= 1000
 *
 *
 *
 * Follow-up: Can you solve the problem in O(1) extra memory space?
 *
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
struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    if (head->next == NULL || k == 1)
    {
        return head;
    }

    struct ListNode *new_head = NULL;
    // last-group-last-node and next-group-first-node and current-node and current-head
    struct ListNode *l_g_l_node = NULL, *n_g_f_node = head, *c_node = head, *c_head, *c_c_node;
    // current-group-size;
    int c_g_s = 1;
    while (1)
    {

        if (c_g_s == k)
        {
            n_g_f_node = c_node->next;
            // reverse current group
            if (l_g_l_node == NULL)
            {
                c_head = head;
            }
            else
            {
                c_head = l_g_l_node->next;
            }
            if (new_head == NULL)
            {
                new_head = c_node;
            }
            else
            {
                l_g_l_node->next = c_node;
            }
            c_c_node = c_node;
            for (int i = k - 1; i > 0; i--)
            {
                c_node = c_head;
                for (int j = 1; j < i; j++)
                {
                    c_node = c_node->next;
                }
                c_c_node->next = c_node;
                c_c_node = c_c_node->next;
            }
            l_g_l_node = c_c_node;
            l_g_l_node->next = n_g_f_node;
            c_node = n_g_f_node;
            if (c_node == NULL)
            {
                break;
            }
            c_g_s = 1;
        }
        else
        {
            c_node = c_node->next;
            if (c_node == NULL)
            {
                break;
            }
            c_g_s++;
        }
    }

    return new_head;
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
    head->next->next->val = 3;
    head->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->val = 4;
    head->next->next->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->next->next->next->next->val = 5;
    head->next->next->next->next->next = NULL;

    reverseKGroup(head, 2);
    return 0;
}
