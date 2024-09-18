/*
 * @lc app=leetcode.cn id=135 lang=c
 *
 * [135] Candy
 *
 * https://leetcode.cn/problems/candy/description/
 *
 * algorithms
 * Hard (48.74%)
 * Likes:    1558
 * Dislikes: 0
 * Total Accepted:    349K
 * Total Submissions: 716K
 * Testcase Example:  '[1,0,2]'
 *
 * There are n children standing in a line. Each child is assigned a rating
 * value given in the integer array ratings.
 *
 * You are giving candies to these children subjected to the following
 * requirements:
 *
 *
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 *
 *
 * Return the minimum number of candies you need to have to distribute the
 * candies to the children.
 *
 *
 * Example 1:
 *
 *
 * Input: ratings = [1,0,2]
 * Output: 5
 * Explanation: You can allocate to the first, second and third child with 2,
 * 1, 2 candies respectively.
 *
 *
 * Example 2:
 *
 *
 * Input: ratings = [1,2,2]
 * Output: 4
 * Explanation: You can allocate to the first, second and third child with 1,
 * 2, 1 candies respectively.
 * The third child gets 1 candy because it satisfies the above two
 * conditions.
 *
 *
 *
 * Constraints:
 *
 *
 * n == ratings.length
 * 1 <= n <= 2 * 10^4
 * 0 <= ratings[i] <= 2 * 10^4
 *
 *
 */

#include <stdlib.h>
#include <math.h>

// @lc code=start
int candy(int *ratings, int ratingsSize)
{
    if (ratingsSize == 1)
    {
        return 1;
    }
    if (ratingsSize == 2)
    {
        return ratings[0] == ratings[1] ? 2 : 3;
    }
    int pre_candies = 1;
    int candies = 1;
    int decrease = 0, increase = 1;

    for (int i = 1; i < ratingsSize; i++)
    {
        if (ratings[i] >= ratings[i - 1])
        {
            decrease = 0;
            pre_candies = ratings[i] == ratings[i - 1] ? 1 : pre_candies + 1;
            candies += pre_candies;
            increase = pre_candies;
        }
        else
        {
            decrease++;
            if (decrease == increase)
            {
                decrease++;
            }
            candies += decrease;
            pre_candies = 1;
        }
    }

    return candies;
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int ratings[5] = {1, 3, 2, 2, 1};
    int candies = candy(ratings, 5);
    return 0;
}
