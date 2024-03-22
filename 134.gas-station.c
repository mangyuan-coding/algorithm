/*
 * @lc app=leetcode.cn id=134 lang=c
 *
 * [134] Gas Station
 */

// @lc code=start
#include <stdlib.h>

int canCompleteCircuit(int *gas, int gasSize, int *cost, int costSize)
{
    int start = 0;
    while (start < gasSize)
    {
        int cur_gas = gas[start] - cost[start];
        if (cur_gas < 0)
        {
            start++;
            continue;
        }

        int travel = (start == gasSize - 1) ? 0 : start + 1;
        while (travel != start)
        {
            cur_gas += (gas[travel] - cost[travel]);
            if (cur_gas < 0)
            {
                break;
            }
            else if (travel == gasSize - 1)
            {
                travel = 0;
            }
            else
            {
                travel++;
            }
        }

        if (travel == start)
        {
            return start;
        }

        if (travel < start)
        {
            return -1;
        }
        start = travel + 1;
    }

    return -1;
}
// @lc code=end