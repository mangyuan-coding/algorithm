/*
 * @lc app=leetcode.cn id=155 lang=c
 *
 * [155] Min Stack
 */

#include <stdio.h>

// @lc code=start
#include <stdlib.h>

typedef struct
{
    int cap;
    int *elems;
    int *min_val;
    int size;
} MinStack;

const int DEFAULT_CAP = 100;
const float FACTOR = 1.5;

MinStack *minStackCreate()
{
    MinStack *stack = (MinStack *)malloc(sizeof(MinStack));
    stack->cap = DEFAULT_CAP;
    stack->elems = (int *)malloc(sizeof(int) * DEFAULT_CAP);
    stack->min_val = (int *)malloc(sizeof(int) * DEFAULT_CAP);
    stack->size = 0;
    return stack;
}

void minStackPush(MinStack *obj, int val)
{
    if (obj->cap == obj->size)
    {
        printf("mark realloc start, cap is %d \n", obj->cap);
        obj->cap = obj->cap * FACTOR;
        obj->elems = (int *)realloc(obj->elems, sizeof(int) * obj->cap);
        obj->min_val = (int *)realloc(obj->min_val, sizeof(int) * obj->cap);
        printf("mark realloc end, cap is %d \n", obj->cap);
    }
    obj->size++;
    obj->elems[obj->size - 1] = val;
    obj->min_val[obj->size - 1] = obj->size == 1 || obj->min_val[obj->size - 2] > val ? val : obj->min_val[obj->size - 2];
}

void minStackPop(MinStack *obj)
{
    obj->size--;
}

int minStackTop(MinStack *obj)
{
    return obj->elems[obj->size - 1];
}

int minStackGetMin(MinStack *obj)
{
    return obj->min_val[obj->size - 1];
}

void minStackFree(MinStack *obj)
{
    free(obj->elems);
    free(obj->min_val);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/
// @lc code=end
