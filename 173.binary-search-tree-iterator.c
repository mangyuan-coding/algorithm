/*
 * @lc app=leetcode.cn id=173 lang=c
 *
 * [173] Binary Search Tree Iterator
 *
 * https://leetcode.cn/problems/binary-search-tree-iterator/description/
 *
 * algorithms
 * Medium (82.25%)
 * Likes:    774
 * Dislikes: 0
 * Total Accepted:    147K
 * Total Submissions: 178.7K
 * Testcase Example:  '["BSTIterator","next","next","hasNext","next","hasNext","next","hasNext","next","hasNext"]\n' +
  '[[[7,3,15,null,null,9,20]],[],[],[],[],[],[],[],[],[]]'
 *
 * Implement the BSTIterator class that represents an iterator over the
 * in-order traversal of a binary search tree (BST):
 *
 *
 * BSTIterator(TreeNode root) Initializes an object of the BSTIterator class.
 * The root of the BST is given as part of the constructor. The pointer should
 * be initialized to a non-existent number smaller than any element in the
 * BST.
 * boolean hasNext() Returns true if there exists a number in the traversal to
 * the right of the pointer, otherwise returns false.
 * int next() Moves the pointer to the right, then returns the number at the
 * pointer.
 *
 *
 * Notice that by initializing the pointer to a non-existent smallest number,
 * the first call to next() will return the smallest element in the BST.
 *
 * You may assume that next() calls will always be valid. That is, there will
 * be at least a next number in the in-order traversal when next() is
 * called.
 *
 *
 * Example 1:
 *
 *
 * Input
 * ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next",
 * "hasNext", "next", "hasNext"]
 * [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
 * Output
 * [null, 3, 7, true, 9, true, 15, true, 20, false]
 *
 * Explanation
 * BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
 * bSTIterator.next();    // return 3
 * bSTIterator.next();    // return 7
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 9
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 15
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 20
 * bSTIterator.hasNext(); // return False
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 10^5].
 * 0 <= Node.val <= 10^6
 * At most 10^5 calls will be made to hasNext, and next.
 *
 *
 *
 * Follow up:
 *
 *
 * Could you implement next() and hasNext() to run in average O(1) time and use
 * O(h) memory, where h is the height of the tree?
 *
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "include/type.h"

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

const int NODE_CAP = 100000;

typedef struct
{
    int idx;
    int size;
    int *value;
} BSTIterator;

void in_order_tree(struct TreeNode *root, BSTIterator *iterator)
{
    if (root->left != NULL)
    {
        in_order_tree(root->left, iterator);
    }
    iterator->value[iterator->size++] = root->val;
    if (root->right != NULL)
    {
        in_order_tree(root->right, iterator);
    }
}

BSTIterator *bSTIteratorCreate(struct TreeNode *root)
{
    BSTIterator *iterator = malloc(sizeof(BSTIterator));
    iterator->idx = 0;
    iterator->size = 0;
    iterator->value = calloc(NODE_CAP, sizeof(int));
    in_order_tree(root, iterator);
    return iterator;
}

int bSTIteratorNext(BSTIterator *obj)
{
    if (obj->size == obj->idx)
    {
        return -1;
    }
    obj->idx++;
    return obj->value[obj->idx - 1];
}

bool bSTIteratorHasNext(BSTIterator *obj)
{
    return obj->size > obj->idx;
}

void bSTIteratorFree(BSTIterator *obj)
{
    free(obj->value);
    free(obj);
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);

 * bool param_2 = bSTIteratorHasNext(obj);

 * bSTIteratorFree(obj);
*/
// @lc code=end

int main(int argc, char const *argv[])
{
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = 7;
    root->left = malloc(sizeof(struct TreeNode));
    root->left->val = 3;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = malloc(sizeof(struct TreeNode));
    root->right->val = 15;
    root->right->left = malloc(sizeof(struct TreeNode));
    root->right->left->val = 9;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = malloc(sizeof(struct TreeNode));
    root->right->right->val = 20;
    root->right->right->left = NULL;
    root->right->right->right = NULL;
    BSTIterator *iterator = bSTIteratorCreate(root);
    printf("%d \n", bSTIteratorNext(iterator));
    printf("%d \n", bSTIteratorNext(iterator));
    printf("%d \n", bSTIteratorHasNext(iterator));
    printf("%d \n", bSTIteratorNext(iterator));
    printf("%d \n", bSTIteratorHasNext(iterator));
    printf("%d \n", bSTIteratorNext(iterator));
    printf("%d \n", bSTIteratorHasNext(iterator));
    return 0;
}
