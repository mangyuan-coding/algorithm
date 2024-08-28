/*
 * @lc app=leetcode.cn id=85 lang=c
 *
 * [85] Maximal Rectangle
 *
 * https://leetcode.cn/problems/maximal-rectangle/description/
 *
 * algorithms
 * Hard (55.30%)
 * Likes:    1663
 * Dislikes: 0
 * Total Accepted:    202.5K
 * Total Submissions: 366.2K
 * Testcase Example:  '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest
 * rectangle containing only 1's and return its area.
 *
 *
 * Example 1:
 *
 *
 * Input: matrix =
 * [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
 * Output: 6
 * Explanation: The maximal rectangle is shown in the above picture.
 *
 *
 * Example 2:
 *
 *
 * Input: matrix = [["0"]]
 * Output: 0
 *
 *
 * Example 3:
 *
 *
 * Input: matrix = [["1"]]
 * Output: 1
 *
 *
 *
 * Constraints:
 *
 *
 * rows == matrix.length
 * cols == matrix[i].length
 * 1 <= row, cols <= 200
 * matrix[i][j] is '0' or '1'.
 *
 *
 */
#include <stdlib.h>
#include <math.h>

// @lc code=start

typedef struct node
{
    int down_size;
    int right_size;
} node;

int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize)
{
    if (matrixSize == 1 && matrixColSize[0] == 1)
    {
        return matrix[0][0] - '0';
    }

    int m = matrixSize, n = matrixColSize[0];
    struct node **nodes = malloc(sizeof(struct node *) * m * n);
    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            int node_idx = i * n + j;
            if (matrix[i][j] == '1')
            {
                nodes[node_idx] = malloc(sizeof(struct node *));
                int down_idx = (i + 1) * n + j;
                if (i < m - 1 && nodes[down_idx] != NULL)
                {
                    nodes[node_idx]->down_size = nodes[down_idx]->down_size + 1;
                }
                else
                {
                    nodes[node_idx]->down_size = 0;
                }
                int right_idx = node_idx + 1;
                if (j < n - 1 && nodes[right_idx] != NULL)
                {
                    nodes[node_idx]->right_size = nodes[right_idx]->right_size + 1;
                }
                else
                {
                    nodes[node_idx]->right_size = 0;
                }
            }
            else
            {
                nodes[node_idx] = NULL;
            }
        }
    }
    int max_area = 0;
    for (int i = 0; i < m * n; i++)
    {
        if (nodes[i] != NULL)
        {
            max_area = fmax(max_area, nodes[i]->right_size + 1);
            max_area = fmax(max_area, nodes[i]->down_size + 1);
            if (nodes[i]->down_size != 0 && nodes[i]->right_size != 0)
            {
                int next_i = i + n + 1;
                int lim_len = nodes[i]->right_size + 1,
                    lim_wid = nodes[i]->down_size + 1;
                int act_len = 1, act_wid = 1;
                struct node *pre = nodes[i], *cur;
                while ((cur = nodes[next_i]) != NULL)
                {
                    act_wid++;
                    lim_wid = fmin(lim_wid, cur->down_size + act_wid);
                    act_len++;
                    lim_len = fmin(lim_len, cur->right_size + act_len);

                    max_area = fmax(max_area, act_len * lim_wid);
                    max_area = fmax(max_area, lim_len * act_wid);

                    if (act_len == lim_len && act_wid == lim_wid)
                    {
                        break;
                    }
                    else if (act_len == lim_len)
                    {
                        act_wid = fmin(lim_wid, cur->down_size + act_wid);
                        break;
                    }
                    else if (act_wid == lim_wid)
                    {
                        act_len = fmin(lim_len, cur->right_size + act_len);
                        break;
                    }
                    else
                    {
                        next_i = next_i + n + 1;
                    }
                }
                max_area = fmax(max_area, act_len * act_wid);
            }
        }
    }

    return max_area;
}
// @lc code=end

int main(int argc, char const *argv[])
{
    int matrixSize = 10;
    int *matrixColSize = malloc(sizeof(int));
    matrixColSize[0] = 7;
    char **matrix = malloc(sizeof(char *) * matrixSize);
    matrix[0] = "0001010";
    matrix[1] = "0100000";
    matrix[2] = "0101001";
    matrix[3] = "0011001";
    matrix[4] = "1111110";
    matrix[5] = "1001011";
    matrix[6] = "0100101";
    matrix[7] = "1101110";
    matrix[8] = "1010101";
    matrix[9] = "1110000";
    maximalRectangle(matrix, matrixSize, matrixColSize);
    return 0;
}
