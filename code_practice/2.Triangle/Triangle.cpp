#include "Triangle.h"
std::vector<std::vector<int> > Solution::generate(int numRows) {
    std::vector<std::vector<int> > nums;
    nums.resize(numRows);

    for (int i = 0; i < numRows; i++)
    {
        nums[i].resize(i+1, 0);
        nums[i][0] = 1;
        nums[i][nums[i].size() - 1] = 1;
    }
    for (int i = 2; i < numRows; i++)
        for(int j = 1; j < i; j++)
        {
            nums[i][j] = nums[i - 1][j] + nums[i - 1][j - 1];
        }
    return nums;
}
