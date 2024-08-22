/*
 * @lc app=leetcode.cn id=51 lang=c
 *
 * [51] N-Queens
 *
 * https://leetcode.cn/problems/n-queens/description/
 *
 * algorithms
 * Hard (74.27%)
 * Likes:    2112
 * Dislikes: 0
 * Total Accepted:    428.6K
 * Total Submissions: 577.1K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n
 * chessboard such that no two queens attack each other.
 *
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * You may return the answer in any order.
 *
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space,
 * respectively.
 *
 *
 * Example 1:
 *
 *
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as
 * shown above
 *
 *
 * Example 2:
 *
 *
 * Input: n = 1
 * Output: [["Q"]]
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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

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

void build_next_row(char ***chessboards, int n, int *size, char **chessboard, int row)
{
    if (row == n)
    {
        (*size)++;
        chessboards[(*size) - 1] = chessboard;
    }
    else
    {
        for (int col = 0; col < n; col++)
        {
            if (chessboard[row][col] != '.')
            {
                if (check(chessboard, n, row, col))
                {
                    char **cloned = clone(chessboard, n);
                    fill(cloned, n, row, col);
                    build_next_row(chessboards, n, size, cloned, row + 1);
                }
            }
        }
        free_chessboard(chessboard, n);
    }
}

void build_0(char ***chessboards, int n, int *size)
{
    for (int col = 0; col < n; col++)
    {
        char **chessboard = empty_chessboard(n);
        fill(chessboard, n, 0, col);
        build_next_row(chessboards, n, size, chessboard, 1);
    }
}

char ***solveNQueens(int n, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    char ***chessboards = malloc(sizeof(char **) * (n * n * n * n));
    if (n == 1)
    {
        (*returnSize)++;
        chessboards[0] = malloc(sizeof(char **));
        chessboards[0][0] = "Q";
        returnColumnSizes[0] = malloc(sizeof(int *));
        returnColumnSizes[0][0] = 1;
        return chessboards;
    }
    if (n == 2 || n == 3)
    {
        return NULL;
    }
    build_0(chessboards, n, returnSize);
    returnColumnSizes[0] = malloc(sizeof(int *) * (*returnSize));
    for (int i = 0; i < *returnSize; i++)
    {
        returnColumnSizes[0][i] = n;
    }
    return chessboards;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *returnSize = malloc(sizeof(int));
    int **returnColumnSizes = malloc(sizeof(int *));
    char ***chessboards = solveNQueens(8, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++)
    {
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf(" %s \n", chessboards[i][j]);
        }
        printf(" \n");
    }
    return 0;
}
