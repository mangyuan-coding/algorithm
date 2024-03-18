/*
 * @lc app=leetcode.cn id=116 lang=c
 *
 * [116] Populating Next Right Pointers in Each Node
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */

struct Node *connect(struct Node *root)
{
    if (root == NULL || root->left == NULL)
    {
        return root;
    }
    struct Node **pre_level = (struct Node **)malloc(sizeof(struct Node *)), **cur_level;
    int pre_level_size = 1, cur_level_size = 0;

    pre_level[0] = root;

    while (1)
    {
        cur_level = (struct Node **)malloc(sizeof(struct Node *) * 2 * pre_level_size);
        for (int i = 0; i < pre_level_size; i++)
        {
            if (pre_level[i]->left == NULL)
            {
                continue;
            }
            cur_level[cur_level_size++] = pre_level[i]->left;
            cur_level[cur_level_size++] = pre_level[i]->right;
            if (cur_level_size > 2)
            {
                cur_level[cur_level_size - 3]->next = cur_level[cur_level_size - 2];
            }
            cur_level[cur_level_size - 2]->next = cur_level[cur_level_size - 1];
        }
        free(pre_level);
        if (cur_level_size == 0)
        {
            free(cur_level_size);
            break;
        }
        pre_level = cur_level;
        pre_level_size = cur_level_size;
        cur_level_size = 0;
    }

    return root;
}
// @lc code=end
