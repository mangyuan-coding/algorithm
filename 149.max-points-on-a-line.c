/*
 * @lc app=leetcode.cn id=149 lang=c
 *
 * [149] Max Points on a Line
 *
 * https://leetcode.cn/problems/max-points-on-a-line/description/
 *
 * algorithms
 * Hard (41.09%)
 * Likes:    565
 * Dislikes: 0
 * Total Accepted:    99.7K
 * Total Submissions: 242.7K
 * Testcase Example:  '[[1,1],[2,2],[3,3]]'
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on
 * the X-Y plane, return the maximum number of points that lie on the same
 * straight line.
 *
 *
 * Example 1:
 *
 *
 * Input: points = [[1,1],[2,2],[3,3]]
 * Output: 3
 *
 *
 * Example 2:
 *
 *
 * Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 * Output: 4
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= points.length <= 300
 * points[i].length == 2
 * -10^4 <= xi, yi <= 10^4
 * All the points are unique.
 *
 *
 */

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "uthash/src/uthash.h"
#include <stdio.h>

// @lc code=start

struct HashTable
{
    int key, val;
    UT_hash_handle hh;
};

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int maxPoints(int **points, int pointsSize, int *pointsColSize)
{
    int n = pointsSize;
    if (n <= 2)
    {
        return n;
    }
    int ret = 0;
    for (int i = 0; i < n; i++)
    {
        if (ret >= n - i || ret > n / 2)
        {
            break;
        }
        struct HashTable *hashTable = NULL;
        for (int j = i + 1; j < n; j++)
        {
            int x = points[i][0] - points[j][0];
            int y = points[i][1] - points[j][1];
            if (x == 0)
            {
                y = 1;
            }
            else if (y == 0)
            {
                x = 1;
            }
            else
            {
                if (y < 0)
                {
                    x = -x;
                    y = -y;
                }
                int gcdXY = gcd(abs(x), abs(y));
                x /= gcdXY, y /= gcdXY;
            }
            struct HashTable *tmp;
            int val = y + x * 20010;
            HASH_FIND_INT(hashTable, &val, tmp);
            if (tmp == NULL)
            {
                tmp = malloc(sizeof(struct HashTable));
                tmp->key = val;
                tmp->val = 1;
                HASH_ADD_INT(hashTable, key, tmp);
            }
            else
            {
                tmp->val++;
            }
        }
        int maxn = 0;
        struct HashTable *iter, *tmp;
        HASH_ITER(hh, hashTable, iter, tmp)
        {
            maxn = fmax(maxn, iter->val + 1);
            HASH_DEL(hashTable, iter);
            free(iter);
        }
        ret = fmax(ret, maxn);
    }
    return ret;
}

// @lc code=end
int main(int argc, char const *argv[])
{
    int *points1[] = {(int[]){3, 3}, (int[]){1, 4}, (int[]){1, 1}, (int[]){2, 1}, (int[]){2, 2}};
    int pints = maxPoints(points1, 5, NULL);

    int *points2[] = {(int[]){1, 1}, (int[]){3, 2}, (int[]){5, 3}, (int[]){4, 1}, (int[]){2, 3}, (int[]){1, 4}};
    pints = maxPoints(points2, 6, NULL);
    return 0;
}
