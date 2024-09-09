/*
 * @lc app=leetcode.cn id=124 lang=c
 *
 * [124] Binary Tree Maximum Path Sum
 *
 * https://leetcode.cn/problems/binary-tree-maximum-path-sum/description/
 *
 * algorithms
 * Hard (45.88%)
 * Likes:    2273
 * Dislikes: 0
 * Total Accepted:    451K
 * Total Submissions: 983.1K
 * Testcase Example:  '[1,2,3]'
 *
 * A path in a binary tree is a sequence of nodes where each pair of adjacent
 * nodes in the sequence has an edge connecting them. A node can only appear in
 * the sequence at most once. Note that the path does not need to pass through
 * the root.
 *
 * The path sum of a path is the sum of the node's values in the path.
 *
 * Given the root of a binary tree, return the maximum path sum of any
 * non-empty path.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,2,3]
 * Output: 6
 * Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 =
 * 6.
 *
 *
 * Example 2:
 *
 *
 * Input: root = [-10,9,20,null,null,15,7]
 * Output: 42
 * Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 +
 * 7 = 42.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 3 * 10^4].
 * -1000 <= Node.val <= 1000
 *
 *
 */

#include "include/type.h"
#include <math.h>

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

long MAX_PATH_SUM = INT32_MIN;

int longest_path(struct TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_longest_path = longest_path(root->left);
    int right_longest_path = longest_path(root->right);

    MAX_PATH_SUM = fmax(MAX_PATH_SUM, root->val);
    MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path + root->val);
    MAX_PATH_SUM = fmax(MAX_PATH_SUM, right_longest_path + root->val);
    MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path + right_longest_path + root->val);

    return fmax(fmax(left_longest_path, right_longest_path), 0) + root->val;
}

int maxPathSum(struct TreeNode *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return root->val;
    }
    MAX_PATH_SUM = INT32_MIN;
    MAX_PATH_SUM = fmax(MAX_PATH_SUM, root->val);

    int right_longest_path, left_longest_path;
    if (root->left == NULL)
    {
        right_longest_path = longest_path(root->right);
        if (root->val > 0)
        {
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, right_longest_path + root->val);
        }
        else
        {
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, right_longest_path);
        }
    }
    else if (root->right == NULL)
    {
        left_longest_path = longest_path(root->left);
        if (root->val > 0)
        {
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path + root->val);
        }
        else
        {
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path);
        }
    }
    else
    {
        left_longest_path = longest_path(root->left);
        right_longest_path = longest_path(root->right);
        if (root->val > 0)
        {
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path + root->val);
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, right_longest_path + root->val);
        }
        else
        {
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path);
            MAX_PATH_SUM = fmax(MAX_PATH_SUM, right_longest_path);
        }
        MAX_PATH_SUM = fmax(MAX_PATH_SUM, left_longest_path + right_longest_path + root->val);
    }

    return MAX_PATH_SUM;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = -6;
    root->left = NULL;
    root->right = malloc(sizeof(struct TreeNode));
    root->right->val = -2;
    root->right->left = NULL;
    root->right->right = malloc(sizeof(struct TreeNode));
    root->right->right->val = 9;
    root->right->right->left = malloc(sizeof(struct TreeNode));
    root->right->right->left->val = -1;
    root->right->right->left->left = malloc(sizeof(struct TreeNode));
    root->right->right->left->left->val = -4;
    root->right->right->left->left->left = NULL;
    root->right->right->left->left->right = NULL;
    root->right->right->left->right = NULL;
    root->right->right->right = malloc(sizeof(struct TreeNode));
    root->right->right->right->val = 5;
    root->right->right->right->left = malloc(sizeof(struct TreeNode));
    root->right->right->right->left->val = -1;
    root->right->right->right->left->left = NULL;
    root->right->right->right->left->right = NULL;
    root->right->right->right->right = NULL;
    maxPathSum(root);
    return 0;
}