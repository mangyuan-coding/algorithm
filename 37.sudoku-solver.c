/*
 * @lc app=leetcode.cn id=37 lang=c
 *
 * [37] Sudoku Solver
 *
 * https://leetcode.cn/problems/sudoku-solver/description/
 *
 * algorithms
 * Hard (67.94%)
 * Likes:    1847
 * Dislikes: 0
 * Total Accepted:    259.9K
 * Total Submissions: 382.5K
 * Testcase Example:  '[["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]'
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * A sudoku solution must satisfy all of the following rules:
 *
 *
 * Each of the digits 1-9 must occur exactly once in each row.
 * Each of the digits 1-9 must occur exactly once in each column.
 * Each of the digits 1-9 must occur exactly once in each of the 9 3x3
 * sub-boxes of the grid.
 *
 *
 * The '.' character indicates empty cells.
 *
 *
 * Example 1:
 *
 *
 * Input: board =
 * [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
 * Output:
 * [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
 * Explanation: The input board is shown above and the only valid solution is
 * shown below:
 *
 *
 *
 *
 *
 * Constraints:
 *
 *
 * board.length == 9
 * board[i].length == 9
 * board[i][j] is a digit or '.'.
 * It is guaranteed that the input board has only one solution.
 *
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "uthash/src/uthash.h"

// @lc code=start
const int size = 9;

enum direct
{
    ROW,
    COL,
    SUB,
};

typedef struct position
{
    int start_x;
    int start_y;
    int sub_idx;
    // 1: row 2:
    enum direct next_direct;
} position;

struct position *find_next_pos(char **board,
                               int *row_remain_size, int *col_remain_size, int *sub_remain_size)
{
    struct position *position = malloc(sizeof(struct position));
    int row_min = size + 1, row_min_idx, col_min = size + 1, col_min_idx, sub_min = size + 1, sub_min_idx;
    for (int i = 0; i < size; i++)
    {
        if (row_remain_size[i] != 0 && row_remain_size[i] < row_min)
        {
            row_min = row_remain_size[i];
            row_min_idx = i;
        }
        if (col_remain_size[i] != 0 && col_remain_size[i] < col_min)
        {
            col_min = col_remain_size[i];
            col_min_idx = i;
        }
        if (sub_remain_size[i] != 0 && sub_remain_size[i] > sub_min)
        {
            sub_min = sub_remain_size[i];
            sub_min_idx = i;
        }
    }
    if (row_min != (size + 1) && row_min <= col_min && row_min <= sub_min)
    {
        position->next_direct = ROW;
        position->start_x = row_min_idx;
        for (int i = 0; i < size; i++)
        {
            if (board[row_min_idx][i] == '.')
            {
                position->start_y = i;
                position->sub_idx = (row_min_idx / 3) * 3 + i / 3;
                break;
            }
        }
    }
    else if (col_min != (size + 1) && col_min <= row_min && col_min <= sub_min)
    {
        position->next_direct = COL;
        position->start_y = col_min_idx;
        for (int i = 0; i < size; i++)
        {
            if (board[i][col_min_idx] == '.')
            {
                position->start_x = i;
                position->sub_idx = (i / 3) * 3 + col_min_idx / 3;
                break;
            }
        }
    }
    else
    {
        if (sub_min == size + 1)
        {
            return NULL;
        }
        position->next_direct = SUB;
        position->sub_idx = sub_min_idx;
        int x = sub_min_idx / 3;
        int y = sub_min_idx % 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[x + i][y + j] == '.')
                {
                    position->start_x = x + i;
                    position->start_y = y + j;
                    break;
                }
            }
        }
    }
    return position;
}

bool fill_chars_check(char **board, struct position *pos, int remains,
                      int *row_remain_size, int *col_remain_size, int *sub_remain_size,
                      bool **row_remains, bool **col_remains, bool **sub_remains)
{
    if (remains == 0)
    {
        return true;
    }

    int row_total = 0;
    int col_total = 0;
    int sub_total = 0;

    bool finded = false;
    switch (pos->next_direct)
    {
    case ROW:
        for (int i = 0; i < size; i++)
        {
            if (row_remains[pos->start_x][i] && col_remains[pos->start_y][i] && sub_remains[pos->sub_idx][i])
            {
                board[pos->start_x][pos->start_y] = i + '1';
                row_remains[pos->start_x][i] = false;
                col_remains[pos->start_y][i] = false;
                sub_remains[pos->sub_idx][i] = false;
                row_remain_size[pos->start_x]--;
                col_remain_size[pos->start_y]--;
                sub_remain_size[pos->sub_idx]--;

                struct position *next;
                if (row_remain_size[pos->start_x] == 0)
                {
                    next = find_next_pos(board, row_remain_size, col_remain_size, sub_remain_size);
                }
                else
                {
                    next = malloc(sizeof(struct position));
                    next->next_direct = ROW;
                    next->start_x = pos->start_x;

                    for (int j = pos->start_y + 1; j < size; j++)
                    {
                        if (board[pos->start_x][j] == '.')
                        {
                            next->start_y = j;
                            next->sub_idx = (pos->start_x / 3) * 3 + j / 3;
                            break;
                        }
                    }
                }

                if (fill_chars_check(board, next, remains - 1,
                                     row_remain_size, col_remain_size, sub_remain_size,
                                     row_remains, col_remains, sub_remains))
                {
                    finded = true;
                    break;
                }
                else
                {
                    board[pos->start_x][pos->start_y] = '.';
                    row_remains[pos->start_x][i] = true;
                    col_remains[pos->start_y][i] = true;
                    sub_remains[pos->sub_idx][i] = true;
                    row_remain_size[pos->start_x]++;
                    col_remain_size[pos->start_y]++;
                    sub_remain_size[pos->sub_idx]++;
                }
            }
        }
        return finded;
    case COL:
        for (int i = 0; i < size; i++)
        {
            if (row_remains[pos->start_x][i] && col_remains[pos->start_y][i] && sub_remains[pos->sub_idx][i])
            {
                board[pos->start_x][pos->start_y] = i + '1';
                row_remains[pos->start_x][i] = false;
                col_remains[pos->start_y][i] = false;
                sub_remains[pos->sub_idx][i] = false;
                row_remain_size[pos->start_x]--;
                col_remain_size[pos->start_y]--;
                sub_remain_size[pos->sub_idx]--;

                struct position *next;
                if (col_remain_size[pos->start_y] == 0)
                {
                    next = find_next_pos(board, row_remain_size, col_remain_size, sub_remain_size);
                }
                else
                {
                    next = malloc(sizeof(struct position));
                    next->next_direct = COL;
                    next->start_y = pos->start_y;

                    for (int j = pos->start_x + 1; j < size; j++)
                    {
                        if (board[j][pos->start_y] == '.')
                        {
                            next->start_x = j;
                            next->sub_idx = (j / 3) * 3 + pos->start_y / 3;
                            break;
                        }
                    }
                }

                if (fill_chars_check(board, next, remains - 1,
                                     row_remain_size, col_remain_size, sub_remain_size,
                                     row_remains, col_remains, sub_remains))
                {
                    finded = true;
                    break;
                }
                else
                {
                    board[pos->start_x][pos->start_y] = '.';
                    row_remains[pos->start_x][i] = true;
                    col_remains[pos->start_y][i] = true;
                    sub_remains[pos->sub_idx][i] = true;
                    row_remain_size[pos->start_x]++;
                    col_remain_size[pos->start_y]++;
                    sub_remain_size[pos->sub_idx]++;
                }
            }
        }
        return finded;
    case SUB:
    default:
        for (int i = 0; i < size; i++)
        {
            if (row_remains[pos->start_x][i] && col_remains[pos->start_y][i] && sub_remains[pos->sub_idx][i])
            {
                board[pos->start_x][pos->start_y] = i + '1';
                row_remains[pos->start_x][i] = false;
                col_remains[pos->start_y][i] = false;
                sub_remains[pos->sub_idx][i] = false;
                row_remain_size[pos->start_x]--;
                col_remain_size[pos->start_y]--;
                sub_remain_size[pos->sub_idx]--;

                struct position *next;
                if (sub_remain_size[pos->sub_idx] == 0)
                {
                    next = find_next_pos(board, row_remain_size, col_remain_size, sub_remain_size);
                }
                else
                {
                    next = malloc(sizeof(struct position));
                    next->next_direct = SUB;
                    next->sub_idx = pos->sub_idx;

                    int x = pos->sub_idx / 3;
                    int y = pos->sub_idx % 3;
                    bool find_p = false;
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            if (board[x + i][y + j] == '.')
                            {
                                next->start_x = x + i;
                                next->start_y = y + j;
                                find_p = true;
                                break;
                            }
                        }
                        if (find_p)
                        {
                            break;
                        }
                    }
                }

                if (fill_chars_check(board, next, remains - 1,
                                     row_remain_size, col_remain_size, sub_remain_size,
                                     row_remains, col_remains, sub_remains))
                {
                    finded = true;
                    break;
                }
                else
                {
                    board[pos->start_x][pos->start_y] = '.';
                    row_remains[pos->start_x][i] = true;
                    col_remains[pos->start_y][i] = true;
                    sub_remains[pos->sub_idx][i] = true;
                    row_remain_size[pos->start_x]++;
                    col_remain_size[pos->start_y]++;
                    sub_remain_size[pos->sub_idx]++;
                }
            }
        }
        return finded;
    }
}

void solveSudoku(char **board, int boardSize, int *boardColSize)
{

    int *row_remain_size = malloc(sizeof(int) * size);
    int *col_remain_size = malloc(sizeof(int) * size);
    int *sub_remain_size = malloc(sizeof(int) * size);

    bool **row_remains = malloc(sizeof(bool *) * size);
    bool **col_remains = malloc(sizeof(bool *) * size);
    bool **sub_remains = malloc(sizeof(bool *) * size);

    for (int i = 0; i < size; i++)
    {
        row_remains[i] = malloc(sizeof(bool) * size);
        col_remains[i] = malloc(sizeof(bool) * size);
        sub_remains[i] = malloc(sizeof(bool) * size);

        row_remain_size[i] = size;
        col_remain_size[i] = size;
        sub_remain_size[i] = size;

        for (int j = 0; j < size; j++)
        {
            row_remains[i][j] = true;
            col_remains[i][j] = true;
            sub_remains[i][j] = true;
        }
    }

    int remains = 0;
    for (int i = 0, sub_idx; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            sub_idx = (i / 3) * 3 + j / 3;
            if (board[i][j] != '.')
            {
                char val = board[i][j];
                row_remains[i][val - '1'] = false;
                col_remains[j][val - '1'] = false;
                sub_remains[sub_idx][val - '1'] = false;
                row_remain_size[i]--;
                col_remain_size[j]--;
                sub_remain_size[sub_idx]--;
            }
            else
            {
                remains++;
            }
        }
    }

    struct position *next_pos = find_next_pos(board,
                                              row_remain_size, col_remain_size, sub_remain_size);

    fill_chars_check(board, next_pos, remains,
                     row_remain_size, col_remain_size, sub_remain_size,
                     row_remains, col_remains, sub_remains);
}
// @lc code=end

int main(int argc, char const *argv[])
{
    char **board = malloc(sizeof(char *) * size);
    for (int i = 0; i < size; i++)
    {
        board[i] = malloc(sizeof(char) * size);
    }

    board[0][0] = '5';
    board[0][1] = '3';
    board[0][2] = '.';
    board[0][3] = '.';
    board[0][4] = '7';
    board[0][5] = '.';
    board[0][6] = '.';
    board[0][7] = '.';
    board[0][8] = '.';
    board[0][9] = '.';
    board[1][0] = '6';
    board[1][1] = '.';
    board[1][2] = '.';
    board[1][3] = '1';
    board[1][4] = '9';
    board[1][5] = '5';
    board[1][6] = '.';
    board[1][7] = '.';
    board[1][8] = '.';
    board[2][0] = '.';
    board[2][1] = '9';
    board[2][2] = '8';
    board[2][3] = '.';
    board[2][4] = '.';
    board[2][5] = '.';
    board[2][6] = '.';
    board[2][7] = '6';
    board[2][8] = '.';
    board[3][0] = '8';
    board[3][1] = '.';
    board[3][2] = '.';
    board[3][3] = '.';
    board[3][4] = '6';
    board[3][5] = '.';
    board[3][6] = '.';
    board[3][7] = '.';
    board[3][8] = '3';
    board[4][0] = '4';
    board[4][1] = '.';
    board[4][2] = '.';
    board[4][3] = '8';
    board[4][4] = '.';
    board[4][5] = '3';
    board[4][6] = '.';
    board[4][7] = '.';
    board[4][8] = '1';
    board[5][0] = '7';
    board[5][1] = '.';
    board[5][2] = '.';
    board[5][3] = '.';
    board[5][4] = '2';
    board[5][5] = '.';
    board[5][6] = '.';
    board[5][7] = '.';
    board[5][8] = '6';
    board[6][0] = '.';
    board[6][1] = '6';
    board[6][2] = '.';
    board[6][3] = '.';
    board[6][4] = '.';
    board[6][5] = '.';
    board[6][6] = '2';
    board[6][7] = '8';
    board[6][8] = '.';
    board[7][0] = '.';
    board[7][1] = '.';
    board[7][2] = '.';
    board[7][3] = '4';
    board[7][4] = '1';
    board[7][5] = '9';
    board[7][6] = '.';
    board[7][7] = '.';
    board[7][8] = '5';
    board[8][0] = '.';
    board[8][1] = '.';
    board[8][2] = '.';
    board[8][3] = '.';
    board[8][4] = '8';
    board[8][5] = '.';
    board[8][6] = '.';
    board[8][7] = '7';
    board[8][8] = '9';
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%c,", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    solveSudoku(board, 9, NULL);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%c,", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
