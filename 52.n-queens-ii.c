/*
 * @lc app=leetcode.cn id=52 lang=c
 *
 * [52] N-Queens II
 *
 * https://leetcode.cn/problems/n-queens-ii/description/
 *
 * algorithms
 * Hard (82.40%)
 * Likes:    519
 * Dislikes: 0
 * Total Accepted:    157.9K
 * Total Submissions: 191.6K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n
 * chessboard such that no two queens attack each other.
 *
 * Given an integer n, return the number of distinct solutions to the n-queens
 * puzzle.
 *
 *
 * Example 1:
 *
 *
 * Input: n = 4
 * Output: 2
 * Explanation: There are two distinct solutions to the 4-queens puzzle as
 * shown.
 *
 *
 * Example 2:
 *
 *
 * Input: n = 1
 * Output: 1
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= n <= 9
 *
 *
 */

#include <stdbool.h>
#include <stdlib.h>

// @lc code=start

char **empty_chessboard(int n)
{
    char **chessboard = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        chessboard[i] = malloc(sizeof(char) * (n + 1));
        for (int j = 0; j <= n; j++)
        {
            chessboard[i][j] = '\0';
        }
    }
    return chessboard;
}

char **clone(char **chessboard, int n)
{
    char **cloned = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
    {
        cloned[i] = malloc(sizeof(char) * (n + 1));
        memcpy(cloned[i], chessboard[i], sizeof(char) * (n + 1));
    }
    return cloned;
}

void free_chessboard(char **chessboard, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(chessboard[i]);
    }
    free(chessboard);
}

bool check(char **chessboard, int n, int row, int col)
{
    for (int i = 0; i < n; i++)
    {
        if (chessboard[i][col] == 'Q')
        {
            return false;
        }
    }

    if (row > 0)
    {
        // diagonals
        for (int pre = 1; pre <= row; pre++)
        {
            if (col >= pre && chessboard[row - pre][col - pre] == 'Q')
            {
                return false;
            }
            if (col + pre < n && chessboard[row - pre][col + pre] == 'Q')
            {
                return false;
            }
        }
    }

    return true;
}

void fill(char **chessboard, int n, int row, int col)
{

    for (int i = 0; i < n; i++)
    {
        chessboard[row][i] = '.';
    }
    for (int i = 0; i < n; i++)
    {
        chessboard[i][col] = '.';
    }

    chessboard[row][col] = 'Q';
    if (row < n - 1)
    {
        // diagonals
        for (int next = 1; next < n - row; next++)
        {
            if (col >= next)
            {
                chessboard[row + next][col - next] = '.';
            }
            if (col + next < n)
            {
                chessboard[row + next][col + next] = '.';
            }
        }
    }
}

int find_next_row(int n, char **chessboard, int row)
{
    if (row == n)
    {
        return 1;
    }
    else
    {
        int size = 0;
        for (int col = 0; col < n; col++)
        {
            if (chessboard[row][col] != '.')
            {
                if (check(chessboard, n, row, col))
                {
                    char **cloned = clone(chessboard, n);
                    fill(cloned, n, row, col);
                    size += find_next_row(n, cloned, row + 1);
                }
            }
        }
        free_chessboard(chessboard, n);
        return size;
    }
}

int totalNQueens(int n)
{
    if (n == 1)
    {
        return 1;
    }
    if (n == 2 || n == 3)
    {
        return 0;
    }

    int size = 0;
    for (int col = 0; col < n; col++)
    {
        char **chessboard = empty_chessboard(n);
        fill(chessboard, n, 0, col);
        size += find_next_row(n, chessboard, 1);
    }

    return size;
}
// @lc code=end
