/*
 * @lc app=leetcode.cn id=117 lang=c
 *
 * [117] Populating Next Right Pointers in Each Node II
 */
#include <stdlib.h>
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
    if (root == NULL)
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
            if (pre_level[i]->left != NULL)
            {
                cur_level[cur_level_size++] = pre_level[i]->left;
                if (cur_level_size > 1)
                {
                    cur_level[cur_level_size - 2]->next = cur_level[cur_level_size - 1];
                }
            }
            if (pre_level[i]->right != NULL)
            {
                cur_level[cur_level_size++] = pre_level[i]->right;
                if (cur_level_size > 1)
                {
                    cur_level[cur_level_size - 2]->next = cur_level[cur_level_size - 1];
                }
            }
        }
        free(pre_level);
        if (cur_level_size == 0)
        {
            free(cur_level);
            break;
        }
        pre_level = cur_level;
        pre_level_size = cur_level_size;
        cur_level_size = 0;
    }

    return root;
}
// @lc code=end
