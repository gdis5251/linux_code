#include "Triangle.h"

int main(void)
{
    std::vector<std::vector<int> > nums;
    nums = Solution::generate(5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            std::cout << nums[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
