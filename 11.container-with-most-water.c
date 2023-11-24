/*
 * @lc app=leetcode id=11 lang=c
 *
 * [11] Container With Most Water
 */

#include "uthash/src/uthash.h"

// @lc code=start
#include <math.h>

// int maxArea_idx(int *height, int left, int right)
// {
//     if (left + 1 == right)
//     {
//         return fmin(height[left], height[right]);
//     }

//     int area = fmin(height[left], height[right]) * (right - left);

//     return fmax(fmax(maxArea_idx(height, left, right - 1), maxArea_idx(height, left + 1, right)), area);
// }

// int maxArea(int *height, int heightSize)
// {
//     if (heightSize <= 1)
//     {
//         return 0;
//     }
//     return maxArea_idx(height, 0, heightSize - 1);
// }

struct node
{
    int left;
    UT_hash_handle hh;
    struct inode *inodes;
};

struct inode
{
    int right;
    int val;
    UT_hash_handle hh;
};

struct node *nodes;

struct inode *find(int left, int right)
{
    struct inode *inodes;
    HASH_FIND_INT(nodes, &left, inodes);
    if (inodes != NULL)
    {
        struct inode *tmp_inode;
        HASH_FIND_INT(nodes, &left, tmp_inode);
        return tmp_inode;
    }
    return inodes;
}

void insert(int left, int right, int val)
{
    struct inode *exist_inodes;
    HASH_FIND_INT(nodes, &left, exist_inodes);
    if (exist_inodes != NULL)
    {
        struct inode *exist;
        HASH_FIND_INT(exist_inodes, &left, exist);
        if (exist == NULL)
        {
            struct inode *tmp_inode = malloc(sizeof(struct inode));
            tmp_inode->right = right, tmp_inode->val = val;
            HASH_ADD_INT(exist_inodes, right, tmp_inode);
        }
        else
        {
            exist->val = val;
        }
    }
    else
    {
        struct node *tmp_node = malloc(sizeof(struct node));
        tmp_node->left = left;
        tmp_node->inodes = NULL;
        HASH_ADD_INT(nodes, left, tmp_node);

        struct inode *tmp_inode = malloc(sizeof(struct inode));
        tmp_inode->right = right, tmp_inode->val = val;
        HASH_ADD_INT(tmp_node->inodes, right, tmp_inode);
    }
}

int maxArea(int *height, int heightSize)
{
    if (heightSize <= 1)
    {
        return 0;
    }

    int interval = 1;
    while (interval < heightSize)
    {
        int limit = heightSize - interval;
        for (int i = 0; i < limit; i++)
        {
            int area = fmin(height[i], height[i + interval]) * interval;
            if (interval == 1)
            {
                insert(i, i + interval, area);
            }
            else
            {
                insert(i, i + interval, fmax(area, fmax(find(i + 1, i + interval)->val, find(i, i + interval - 1)->val)));
            }
        }
        interval++;
    }

    return find(0, heightSize - 1)->val;
}

// @lc code=end

#include <stdio.h>

int main(int argc, char const *argv[])
{

    int height[] = {1, 2, 3, 4, 5};
    printf("max-area is %d", maxArea(height, 4));
    return 0;
}
