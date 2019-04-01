#include <vector>
#include <iostream>

int main(void)
{
    int arr[] = { 1, 2, 3, 4 };
    std::vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));
    
    std::vector<int>::iterator it_begin = v1.begin();
    std::vector<int>::iterator it_end = v1.end() - 1;
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
