/*
 * @lc app=leetcode.cn id=174 lang=c
 *
 * [174] Dungeon Game
 *
 * https://leetcode.cn/problems/dungeon-game/description/
 *
 * algorithms
 * Hard (48.57%)
 * Likes:    854
 * Dislikes: 0
 * Total Accepted:    78.5K
 * Total Submissions: 161.6K
 * Testcase Example:  '[[-2,-3,3],[-5,-10,1],[10,30,-5]]'
 *
 * The demons had captured the princess and imprisoned her in the bottom-right
 * corner of a dungeon. The dungeon consists of m x n rooms laid out in a 2D
 * grid. Our valiant knight was initially positioned in the top-left room and
 * must fight his way through dungeon to rescue the princess.
 *
 * The knight has an initial health point represented by a positive integer. If
 * at any point his health point drops to 0 or below, he dies immediately.
 *
 * Some of the rooms are guarded by demons (represented by negative integers),
 * so the knight loses health upon entering these rooms; other rooms are either
 * empty (represented as 0) or contain magic orbs that increase the knight's
 * health (represented by positive integers).
 *
 * To reach the princess as quickly as possible, the knight decides to move
 * only rightward or downward in each step.
 *
 * Return the knight's minimum initial health so that he can rescue the
 * princess.
 *
 * Note that any room can contain threats or power-ups, even the first room the
 * knight enters and the bottom-right room where the princess is imprisoned.
 *
 *
 * Example 1:
 *
 *
 * Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
 * Output: 7
 * Explanation: The initial health of the knight must be at least 7 if he
 * follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
 *
 *
 * Example 2:
 *
 *
 * Input: dungeon = [[0]]
 * Output: 1
 *
 *
 *
 * Constraints:
 *
 *
 * m == dungeon.length
 * n == dungeon[i].length
 * 1 <= m, n <= 200
 * -1000 <= dungeon[i][j] <= 1000
 *
 *
 */
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// @lc code=start
int calculateMinimumHP(int **dungeon, int dungeonSize, int *dungeonColSize)
{
    int n = dungeonSize, m = dungeonColSize[0];
    int dp[n + 1][m + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[n][m - 1] = dp[n - 1][m] = 1;
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = m - 1; j >= 0; --j)
        {
            int minn = fmin(dp[i + 1][j], dp[i][j + 1]);
            dp[i][j] = fmax(minn - dungeon[i][j], 1);
        }
    }
    return dp[0][0];
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int *dungeon[] = {(int[]){0, -5}, (int[]){0, 0}};
    int hp = calculateMinimumHP(dungeon, 2, (int[]){2});
    return 0;
}
