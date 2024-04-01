/*
 * @lc app=leetcode.cn id=150 lang=c
 *
 * [150] Evaluate Reverse Polish Notation
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum operator
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    NUMBER
} operator;

enum operator convert(char *token)
{
    int len = strlen(token);
    if (len == 1)
    {
        switch (token[0])
        {
        case '+':
            return ADD;
        case '-':
            return SUBTRACT;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
        default:
            break;
        }
    }
    return NUMBER;
}

int evalRPN(char **tokens, int tokensSize)
{
    if (tokensSize == 1)
    {
        return atoi(tokens[0]);
    }

    int *operands = (int *)malloc(sizeof(int) * tokensSize), op_size = 0;
    operands[op_size++] = atoi(tokens[0]);

    int idx = 1;
    enum operator op;
    while (idx < tokensSize)
    {
        switch (op = convert(tokens[idx]))
        {
        case ADD:
            operands[op_size - 2] += operands[op_size - 1];
            op_size--;
            break;
        case SUBTRACT:
            operands[op_size - 2] -= operands[op_size - 1];
            op_size--;
            break;
        case MULTIPLY:
            operands[op_size - 2] *= operands[op_size - 1];
            op_size--;
            break;
        case DIVIDE:
            operands[op_size - 2] /= operands[op_size - 1];
            op_size--;
            break;
        case NUMBER:
            operands[op_size++] = atoi(tokens[idx]);
            break;
        default:
            break;
        }
        idx++;
    }

    return operands[0];
}
// @lc code=end
int main(int argc, char const *argv[])
{

    char *tokens[7] = {"4", "-2", "/", "2", "-3", "-", "-"};
    evalRPN(tokens, 7);
    return 0;
}
