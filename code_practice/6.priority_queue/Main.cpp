#include <iostream>
#include <functional>
#include <queue>
#include <vector>


int main(void)
{
    std::priority_queue<int> pq;
    std::vector<int> v;
    
    v.push_back(1);
    v.push_back(8);
    v.push_back(3);
    v.push_back(6);
    v.push_back(2);
    v.push_back(4);
    for(const auto& e : v)
    {
        pq.push(e);
    }

    std::cout << pq.top() << std::endl;

    std::priority_queue<int, std::vector<int>, std::greater<int> > pq1(v.begin(), v.end());
    std::cout << pq1.top() << std::endl;

    return 0;
}
