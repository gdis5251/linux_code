#include <vector>
#include <iostream>

int main(void)
{
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    
    std::vector<int>::iterator it_begin = v1.begin();
    std::vector<int>::iterator it_end = v1.end() - 1;
    while (it_begin <= it_end)
    {
        std::cout << *it_begin << " ";
        it_begin++;
    }
    std::cout << std::endl;
    it_begin = v1.begin();
    v1.insert(v1.begin() + 1, 10);

    std::cout << *it_begin << std::endl;
    std::cout << *it_end << std::endl;
    while (it_begin <= it_end)
    {
        std::cout << *it_begin << " ";
        it_begin++;
    }
    std::cout << std::endl;

    return 0;
}
