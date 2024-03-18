#include "type.h"
#include <string.h>

int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

typedef struct Integer
{
    int val;
} Integer;

const char *STR_NULL = "null";

struct TreeNode *build_tree(char *nums_str, int muns_size)
{
    int len = strlen(nums_str);
    char *dyn_nums_str = (char *)malloc(sizeof(char) * (len + 1));
    memcpy(dyn_nums_str, nums_str, sizeof(char) * len);
    dyn_nums_str[len] = '\0';

    char *each_num = strtok(dyn_nums_str, ",");

    struct Integer **integers = (struct Integer **)malloc(sizeof(struct Integer *) * muns_size);
    integers[0] = (struct Integer *)malloc(sizeof(struct Integer));
    integers[0]->val = atoi(each_num);
    for (int i = 1; i < muns_size; i++)
    {
        char *each_num = strtok(NULL, ",");
        if (strcmp(STR_NULL, each_num) == 0)
        {
            integers[i] = NULL;
        }
        else
        {
            integers[i] = (struct Integer *)malloc(sizeof(struct Integer));
            integers[i]->val = atoi(each_num);
        }
    }

    struct TreeNode **pre_level = (struct TreeNode **)malloc(sizeof(struct TreeNode *)), **cur_level;
    int pre_level_size = 1, cur_level_size = 0;
    pre_level[0] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    pre_level[0]->val = integers[0]->val;

    struct TreeNode *root = pre_level[0];

    int idx = 1, pre_idx = 0;
    cur_level = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * 2);
    while (1)
    {
        if (pre_idx == pre_level_size)
        {
            free(pre_level);
            pre_level = cur_level;
            pre_level_size = cur_level_size;
            cur_level_size = 0;
            cur_level = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * 2 * pre_level_size);
            pre_idx = 0;
        }
        else
        {
            if (integers[idx] != NULL)
            {
                pre_level[pre_idx]->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                pre_level[pre_idx]->left->val = integers[idx]->val;
                cur_level[cur_level_size++] = pre_level[pre_idx]->left;
            }
            else
            {
                pre_level[pre_idx]->left = NULL;
            }

            idx++;
            if (idx == muns_size)
            {
                break;
            }

            if (integers[idx] != NULL)
            {
                pre_level[pre_idx]->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                pre_level[pre_idx]->right->val = integers[idx]->val;
                cur_level[cur_level_size++] = pre_level[pre_idx]->right;
            }
            else
            {
                pre_level[pre_idx]->right = NULL;
            }

            idx++;
            if (idx == muns_size)
            {
                break;
            }
            pre_idx++;
        }
    }

    for (int i = 0; i < cur_level_size; i++)
    {
        cur_level[i]->left = NULL;
        cur_level[i]->right = NULL;
    }

    return root;
}