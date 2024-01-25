/*
 * @lc app=leetcode id=75 lang=c
 *
 * [75] Sort Colors
 */

// @lc code=start
void sortColors(int *nums, int numsSize)
{
    int left = 0, right = numsSize - 1;
    while (left < right)
    {
        if (nums[left] == 0)
        {
            left++;
        }
        else if (nums[right] != 0)
        {
            right--;
        }
        else
        {
            int tmp = nums[right];
            nums[right] = nums[left];
            nums[left] = tmp;
            left++;
            right--;
        }
    }
    if (nums[left] == 0)
    {
        left++;
    }
    right = numsSize - 1;
    while (left < right)
    {
        if (nums[right] == 2)
        {
            right--;
        }
        else if (nums[left] == 1)
        {
            left++;
        }
        else
        {
            int tmp = nums[right];
            nums[right] = nums[left];
            nums[left] = tmp;
            left++;
            right--;
        }
    }
}
// @lc code=end
int main(int argc, char const *argv[])
{
    int nums[3] = {1, 0, 0};
    sortColors(nums, 3);
    return 0;
}
