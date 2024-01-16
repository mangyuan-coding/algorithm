/*
 * @lc app=leetcode id=71 lang=c
 *
 * [71] Simplify Path
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>

char *simplifyPath(char *path)
{
    int len = strlen(path);

    char *simple_path = (char *)malloc(sizeof(char) * (len + 1));

    int idx_of_simple_path = 0;
    simple_path[idx_of_simple_path++] = '/';

    int last_slash_idx = 0;
    for (int idx_of_path = 1; idx_of_path <= len; idx_of_path++)
    {
        if (idx_of_path == len || path[idx_of_path] == '/')
        {
            int distance = idx_of_path - last_slash_idx;

            if (distance == 1)
            {
            }
            else if (distance == 2)
            {
                // .
                if (path[idx_of_path - 1] == '.')
                {
                }
                else
                {
                    simple_path[idx_of_simple_path++] = path[idx_of_path - 1];
                    simple_path[idx_of_simple_path++] = '/';
                }
            }
            else if (distance == 3)
            {
                // ..
                if (path[idx_of_path - 1] == '.' && path[idx_of_path - 2] == '.')
                {
                    if (idx_of_simple_path > 1)
                    {
                        idx_of_simple_path -= 2;
                        while (idx_of_simple_path > 0)
                        {
                            if (simple_path[idx_of_simple_path] == '/')
                            {
                                break;
                            }
                            idx_of_simple_path--;
                        }
                        idx_of_simple_path++;
                    }
                }
                else
                {
                    simple_path[idx_of_simple_path++] = path[idx_of_path - 2];
                    simple_path[idx_of_simple_path++] = path[idx_of_path - 1];
                    simple_path[idx_of_simple_path++] = '/';
                }
            }
            else
            {
                memcpy(simple_path + idx_of_simple_path, path + last_slash_idx + 1, distance - 1);
                idx_of_simple_path += (distance - 1);
                simple_path[idx_of_simple_path++] = '/';
            }

            last_slash_idx = idx_of_path;
        }
    }

    if (idx_of_simple_path == 1)
    {
        simple_path[idx_of_simple_path] = '\0';
    }
    else if (simple_path[idx_of_simple_path - 1] == '/')
    {
        simple_path[idx_of_simple_path - 1] = '\0';
    }
    else
    {
        simple_path[idx_of_simple_path] = '\0';
    }
    return simple_path;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%s", simplifyPath("/a//b////c/d//././/.."));
    return 0;
}
