/*
 * @lc app=leetcode id=48 lang=c
 *
 * [48] Rotate Image
 */

// @lc code=start
void rotate(int **matrix, int matrixSize, int *matrixColSize)
{
    if (matrixColSize <= 1)
    {
        return;
    }

    // (idx_each_rectangle                 , idx_each_rectangle) (idx_each_rectangle                 , idx_each_rectangle + 1) ... (idx_each_rectangle                 , matrixSize - idx_each_rectangle - 2) (idx_each_rectangle                , matrixSize - idx_each_rectangle - 1)
    // (idx_each_rectangle + 1             , idx_each_rectangle)                                                                                                                                              (idx_each_rectangle + 1            , matrixSize - idx_each_rectangle - 1)
    // .                                                                                                                                                                                                                                          .
    // .                                                                                                                                                                                                                                          .
    // .                                                                                                                                                                                                                                          .
    // (matrixSize - idx_each_rectangle - 2, idx_each_rectangle)                                                                                                                                              (matrixSize - idx_each_rectangle - 2, matrixSize - idx_each_rectangle - 1)
    // (matrixSize - idx_each_rectangle - 1, idx_each_rectangle) (matrixSize - idx_each_rectangle - 1, idx_each_rectangle + 1) ... (matrixSize - idx_each_rectangle - 1, matrixSize - idx_each_rectangle - 2) (matrixSize - idx_each_rectangle - 1, matrixSize - idx_each_rectangle - 1)
    for (int idx_each_rectangle = 0; idx_each_rectangle < matrixSize / 2; idx_each_rectangle++)
    {
        if (idx_each_rectangle == matrixSize - idx_each_rectangle - 1)
        {
            break;
        }

        for (int idx_row = 0; idx_row <= matrixSize - 2 * idx_each_rectangle - 2; idx_row++)
        {
            // first (idx_each_rectangle, idx_each_rectangle + idx_row)
            // second (matrixSize - idx_each_rectangle - 1 - idx_row, idx_each_rectangle)
            // third (matrixSize - idx_each_rectangle - 1, matrixSize - idx_each_rectangle - 1 - idx_row)
            // fourth (idx_each_rectangle + idx_row, matrixSize - idx_each_rectangle - 1)

            // first <=> second
            int tmp = matrix[idx_each_rectangle][idx_each_rectangle + idx_row];
            matrix[idx_each_rectangle][idx_each_rectangle + idx_row] = matrix[matrixSize - idx_each_rectangle - 1 - idx_row][idx_each_rectangle];
            matrix[matrixSize - idx_each_rectangle - 1 - idx_row][idx_each_rectangle] = tmp;

            // second <=> third
            tmp = matrix[matrixSize - idx_each_rectangle - 1 - idx_row][idx_each_rectangle];
            matrix[matrixSize - idx_each_rectangle - 1 - idx_row][idx_each_rectangle] = matrix[matrixSize - idx_each_rectangle - 1][matrixSize - idx_each_rectangle - 1 - idx_row];
            matrix[matrixSize - idx_each_rectangle - 1][matrixSize - idx_each_rectangle - 1 - idx_row] = tmp;

            // third <=> fourth
            tmp = matrix[matrixSize - idx_each_rectangle - 1][matrixSize - idx_each_rectangle - 1 - idx_row];
            matrix[matrixSize - idx_each_rectangle - 1][matrixSize - idx_each_rectangle - 1 - idx_row] = matrix[idx_each_rectangle + idx_row][matrixSize - idx_each_rectangle - 1];
            matrix[idx_each_rectangle + idx_row][matrixSize - idx_each_rectangle - 1] = tmp;
        }
    }
}
// @lc code=end
