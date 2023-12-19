/*
 * @lc app=leetcode id=36 lang=c
 *
 * [36] Valid Sudoku
 */

// @lc code=start
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValidSudoku(char **board, int boardSize, int *boardColSize)
{
    bool **row = (bool **)malloc(sizeof(bool *) * 9);
    bool **column = (bool **)malloc(sizeof(bool *) * 9);
    bool **sub = (bool **)malloc(sizeof(bool *) * 9);
    for (int i = 0; i < 9; i++)
    {
        row[i] = (bool *)malloc(sizeof(bool) * 9);
        column[i] = (bool *)malloc(sizeof(bool) * 9);
        sub[i] = (bool *)malloc(sizeof(bool) * 9);
        for (int j = 0; j < 9; j++)
        {
            row[i][j] = false;
            column[i][j] = false;
            sub[i][j] = false;
        }
    }

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < *boardColSize; j++)
        {
            if (board[i][j] == '.')
            {
                continue;
            }
            int num = board[i][j] - '1';

            if (row[i][num] || column[j][num] || sub[(i / 3) * 3 + j / 3][num])
            {
                return false;
            }
            row[i][num] = true;
            column[j][num] = true;
            sub[(i / 3) * 3 + j / 3][num] = true;
        }
    }
    return true;
}
// @lc code=end

int main(int argc, char const *argv[])
{
    char **board = (char **)malloc(sizeof(char *) * 9);
    board[0] = "53..7....";
    board[1] = "6..195...";
    board[2] = ".98....6.";
    board[3] = "8...6...3";
    board[4] = "4..8.3..1";
    board[5] = "7...2...6";
    board[6] = ".6....28.";
    board[7] = "...419..5";
    board[8] = "....8..79";

    int boardColSize = 9;
    isValidSudoku(board, 9, &boardColSize);
    return 0;
}
