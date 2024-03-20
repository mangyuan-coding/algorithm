/*
 * @lc app=leetcode.cn id=130 lang=c
 *
 * [130] Surrounded Regions
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

typedef enum Direction
{
    U,
    D,
    L,
    R,
} Direction;

void seek(char **board, int m, int n, int seek_x, int seek_y, bool *o_idx, bool *trace)
{
    trace[seek_x * n + seek_y] = true;
    if (board[seek_x][seek_y] == 'O')
    {
        o_idx[seek_x * n + seek_y] = true;
        enum Direction *step = (enum Direction *)malloc(sizeof(enum Direction) * (m * n));
        int step_times = 0;
        while (true)
        {
            // turn L
            if (seek_y > 1 && !trace[seek_x * n + seek_y - 1])
            {
                trace[seek_x * n + seek_y - 1] = true;
                if (board[seek_x][seek_y - 1] == 'O')
                {
                    seek_y--;
                    o_idx[seek_x * n + seek_y] = true;
                    step[step_times++] = L;
                    continue;
                }
            }
            // turn D
            if (seek_x < m - 2 && !trace[(seek_x + 1) * n + seek_y])
            {
                trace[(seek_x + 1) * n + seek_y] = true;
                if (board[seek_x + 1][seek_y] == 'O')
                {
                    seek_x++;
                    o_idx[seek_x * n + seek_y] = true;
                    step[step_times++] = D;
                    continue;
                }
            }
            // turn R
            if (seek_y < n - 2 && !trace[seek_x * n + seek_y + 1])
            {
                trace[seek_x * n + seek_y + 1] = true;
                if (board[seek_x][seek_y + 1] == 'O')
                {
                    seek_y++;
                    o_idx[seek_x * n + seek_y] = true;
                    step[step_times++] = R;
                    continue;
                }
            }
            // turn UP
            if (seek_x > 1 && !trace[(seek_x - 1) * n + seek_y])
            {
                trace[(seek_x - 1) * n + seek_y] = true;
                if (board[seek_x - 1][seek_y] == 'O')
                {
                    seek_x--;
                    o_idx[seek_x * n + seek_y] = true;
                    step[step_times++] = U;
                    continue;
                }
            }
            if (step_times == 0)
            {
                break;
            }
            // back
            switch (step[step_times - 1])
            {
            case L:
                seek_y++;
                break;
            case D:
                seek_x--;
                break;
            case R:
                seek_y--;
                break;
            case U:
                seek_x++;
            default:
                break;
            }
            step_times--;
        }
    }
}

void solve(char **board, int boardSize, int *boardColSize)
{
    if (boardSize <= 2 || boardColSize[0] <= 2)
    {
        return;
    }
    int m = boardSize, n = boardColSize[0];
    bool *o_idx = (bool *)malloc(sizeof(bool) * (m * n));
    bool *trace = (bool *)malloc(sizeof(bool) * (m * n));
    for (int i = 0; i < m * n; i++)
    {
        o_idx[i] = false;
        trace[i] = false;
    }

    // start at edge
    int x = 0, y = 0;

    // top edge
    for (; y < n; y++)
    {
        trace[x * n + y] = true;
        /* code */
        if (board[x][y] == 'O')
        {
            o_idx[x * n + y] = true;
            // turn down

            seek(board, m, n, x + 1, y, o_idx, trace);
        }
    }
    y--;
    x++;
    // right edge
    for (; x < m; x++)
    {
        trace[x * n + y] = true;
        /* code */
        if (board[x][y] == 'O')
        {
            o_idx[x * n + y] = true;
            seek(board, m, n, x, y - 1, o_idx, trace);
        }
    }
    x--;
    y--;
    // bottom edge
    for (; y >= 0; y--)
    {
        trace[x * n + y] = true;
        /* code */
        if (board[x][y] == 'O')
        {
            o_idx[x * n + y] = true;
            // turn up
            seek(board, m, n, x - 1, y, o_idx, trace);
        }
    }
    y++;
    x--;
    // left edge
    for (; x > 0; x--)
    {
        trace[x * n + y] = true;
        /* code */
        if (board[x][y] == 'O')
        {
            o_idx[x * n + y] = true;
            // turn right
            seek(board, m, n, x, y + 1, o_idx, trace);
        }
    }
    // clear
    for (int x = 0; x < m; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (board[x][y] == 'O' && !o_idx[x * n + y])
            {
                board[x][y] = 'X';
            }
        }
    }
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int boardSize = 5;
    int *boardColSize = (int *)malloc(sizeof(int) * boardSize);
    char **board = (char **)malloc(sizeof(char *) * boardSize);
    for (int i = 0; i < boardSize; i++)
    {
        boardColSize[i] = 5;
        board[i] = (char *)malloc(sizeof(char) * boardColSize[i]);
    }
    board[0][0] = 'O';
    board[0][1] = 'X';
    board[0][2] = 'X';
    board[0][3] = 'O';
    board[0][4] = 'X';
    board[1][0] = 'X';
    board[1][1] = 'O';
    board[1][2] = 'O';
    board[1][3] = 'X';
    board[1][4] = 'O';
    board[2][0] = 'X';
    board[2][1] = 'O';
    board[2][2] = 'X';
    board[2][3] = 'O';
    board[2][4] = 'X';
    board[3][0] = 'O';
    board[3][1] = 'X';
    board[3][2] = 'O';
    board[3][3] = 'O';
    board[3][4] = 'O';
    board[4][0] = 'X';
    board[4][1] = 'X';
    board[4][2] = 'O';
    board[4][3] = 'X';
    board[4][4] = 'O';
    solve(board, boardSize, boardColSize);
    return 0;
}
