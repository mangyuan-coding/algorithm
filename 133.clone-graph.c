/*
 * @lc app=leetcode.cn id=133 lang=c
 *
 * [133] Clone Graph
 */

#include <stdio.h>

struct Node
{
    int val;
    int numNeighbors;
    struct Node **neighbors;
};

// @lc code=start
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */
#include <stdlib.h>

const int MAX_NODE_SIZE = 100;

struct Node *clone(struct Node **clones, struct Node *node)
{
    if (clones[node->val - 1] != NULL)
    {
        return clones[node->val - 1];
    }

    struct Node *cloned = (struct Node *)malloc(sizeof(struct Node));
    cloned->val = node->val;
    clones[cloned->val - 1] = cloned;

    cloned->numNeighbors = 0;
    if (node->numNeighbors == 0)
    {

        if (node->neighbors != NULL)
        {
            cloned->neighbors = (struct Node **)malloc(0);
        }
    }
    else
    {
        for (int i = 0; i < node->numNeighbors; i++)
        {
            clone(clones, node->neighbors[i]);
        }
    }

    return cloned;
}

void connect(struct Node **clones, struct Node *node)
{
    struct Node *cloned = clones[node->val - 1];
    if (node->numNeighbors > 0)
    {
        if (cloned->numNeighbors == 0)
        {
            cloned->neighbors = (struct Node **)malloc(sizeof(struct Node *) * node->numNeighbors);
            for (int i = 0; i < node->numNeighbors; i++)
            {
                cloned->neighbors[i] = clones[node->neighbors[i]->val - 1];
                cloned->numNeighbors++;
            }
            for (int i = 0; i < node->numNeighbors; i++)
            {
                connect(clones, node->neighbors[i]);
            }
        }
    }
}

struct Node *cloneGraph(struct Node *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    struct Node **clones = (struct Node **)malloc(sizeof(struct Node *) * MAX_NODE_SIZE);
    for (int i = 0; i < MAX_NODE_SIZE; i++)
    {
        clones[i] = NULL;
    }
    struct Node *cloned = clone(clones, s);
    connect(clones, s);
    return cloned;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    struct Node *s_1 = (struct Node *)malloc(sizeof(struct Node));
    s_1->val = 1;
    s_1->numNeighbors = 2;
    s_1->neighbors = (struct Node **)malloc(sizeof(struct Node *) * 2);
    struct Node *s_2 = (struct Node *)malloc(sizeof(struct Node));
    s_2->val = 2;
    s_2->numNeighbors = 2;
    s_2->neighbors = (struct Node **)malloc(sizeof(struct Node *) * 2);
    struct Node *s_3 = (struct Node *)malloc(sizeof(struct Node));
    s_3->val = 3;
    s_3->numNeighbors = 2;
    s_3->neighbors = (struct Node **)malloc(sizeof(struct Node *) * 2);
    struct Node *s_4 = (struct Node *)malloc(sizeof(struct Node));
    s_4->val = 4;
    s_4->numNeighbors = 2;
    s_4->neighbors = (struct Node **)malloc(sizeof(struct Node *) * 2);
    s_1->neighbors[0] = s_2;
    s_1->neighbors[1] = s_4;
    s_2->neighbors[0] = s_1;
    s_2->neighbors[1] = s_3;
    s_3->neighbors[0] = s_2;
    s_3->neighbors[1] = s_4;
    s_4->neighbors[0] = s_3;
    s_4->neighbors[1] = s_1;

    struct Node *cloned = cloneGraph(s_1);
    return 0;
}
