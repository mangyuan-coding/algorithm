/*
 * @lc app=leetcode id=79 lang=c
 *
 * [79] Word Search
 */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// @lc code=start
enum direction
{
    // UP
    U,
    // DOWN
    D,
    // LEFT
    L,
    // RIGHT
    R,
};

bool exist(char **board, int boardSize, int *boardColSize, char *word)
{
    int len = strlen(word);

    if (len > boardSize * boardColSize[0])
    {
        return false;
    }

    enum direction *trace = (enum direction *)malloc(sizeof(enum direction) * len);
    int trace_idx = 0;

    for (int m = 0; m < boardSize; m++)
    {
        for (int n = 0; n < boardColSize[m]; n++)
        {
            if (word[0] == board[m][n])
            {
                int x = m, y = n, idx_of_word = 1;
                board[x][y] = ' ';
                trace_idx = 0;

                while (1)
                {
                    if (idx_of_word == len)
                    {
                        return true;
                    }
                    if (x > 0 && word[idx_of_word] == board[x - 1][y])
                    {
                        trace[trace_idx++] = U;
                        idx_of_word++;
                        x--;
                        board[x][y] = ' ';
                    }
                    else if (x < boardSize - 1 && word[idx_of_word] == board[x + 1][y])
                    {
                        trace[trace_idx++] = D;
                        idx_of_word++;
                        x++;
                        board[x][y] = ' ';
                    }
                    else if (y > 0 && word[idx_of_word] == board[x][y - 1])
                    {
                        trace[trace_idx++] = L;
                        idx_of_word++;
                        y--;
                        board[x][y] = ' ';
                    }
                    else if (y < boardColSize[m] - 1 && word[idx_of_word] == board[x][y + 1])
                    {
                        trace[trace_idx++] = R;
                        idx_of_word++;
                        y++;
                        board[x][y] = ' ';
                    }
                    else
                    {
                        bool finded = false;
                        while (trace_idx > 0)
                        {
                            switch (trace[trace_idx - 1])
                            {
                            case U:
                                board[x][y] = word[idx_of_word - 1];
                                x++;
                                idx_of_word--;
                                trace_idx--;
                                if (x < boardSize - 1 && word[idx_of_word] == board[x + 1][y])
                                {
                                    trace[trace_idx++] = D;
                                    idx_of_word++;
                                    x++;
                                    board[x][y] = ' ';
                                    finded = true;
                                }
                                else if (y > 0 && word[idx_of_word] == board[x][y - 1])
                                {
                                    trace[trace_idx++] = L;
                                    idx_of_word++;
                                    y--;
                                    board[x][y] = ' ';
                                    finded = true;
                                }
                                else if (y < boardColSize[m] - 1 && word[idx_of_word] == board[x][y + 1])
                                {
                                    trace[trace_idx++] = R;
                                    idx_of_word++;
                                    y++;
                                    board[x][y] = ' ';
                                    finded = true;
                                }
                                break;
                            case D:
                                board[x][y] = word[idx_of_word - 1];
                                x--;
                                idx_of_word--;
                                trace_idx--;
                                if (y > 0 && word[idx_of_word] == board[x][y - 1])
                                {
                                    trace[trace_idx++] = L;
                                    idx_of_word++;
                                    y--;
                                    board[x][y] = ' ';
                                    finded = true;
                                }
                                else if (y < boardColSize[m] - 1 && word[idx_of_word] == board[x][y + 1])
                                {
                                    trace[trace_idx++] = R;
                                    idx_of_word++;
                                    y++;
                                    board[x][y] = ' ';
                                    finded = true;
                                }
                                break;
                            case L:
                                board[x][y] = word[idx_of_word - 1];
                                y++;
                                idx_of_word--;
                                trace_idx--;
                                if (y < boardColSize[m] - 1 && word[idx_of_word] == board[x][y + 1])
                                {
                                    trace[trace_idx++] = R;
                                    idx_of_word++;
                                    y++;
                                    board[x][y] = ' ';
                                    finded = true;
                                }
                                break;
                            case R:
                                board[x][y] = word[idx_of_word - 1];
                                y--;
                                idx_of_word--;
                                trace_idx--;
                            default:
                                break;
                            }
                            if (finded)
                            {
                                break;
                            }
                        }

                        if (!finded)
                        {
                            board[x][y] = word[0];
                            break;
                        }
                    }
                }
            }
        }
    }

    return false;
}
// @lc code=end
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char **board = (char **)malloc(sizeof(char *) * 3);
    board[0] = (char *)malloc(sizeof(char) * 3);
    board[0][0] = 'C';
    board[0][1] = 'A';
    board[0][2] = 'A';
    board[1] = (char *)malloc(sizeof(char) * 3);
    board[1][0] = 'A';
    board[1][1] = 'A';
    board[1][2] = 'A';
    board[2] = (char *)malloc(sizeof(char) * 3);
    board[2][0] = 'B';
    board[2][1] = 'C';
    board[2][2] = 'D';
    int *boardColSize = (int *)malloc(sizeof(int) * 3);
    boardColSize[0] = 3;
    boardColSize[1] = 3;
    boardColSize[2] = 3;
    bool existed = exist(board, 3, boardColSize, "AAB");
    return 0;
}
