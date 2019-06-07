#include "ThreadPool.hpp"


// 这个类由用户自己定制
// 需要依赖哪些数据，都可以随意添加和修改
class MyTask : public Task
{
public:
    MyTask(int id)
        :id_(id)
    {

    }
    virtual void Run()
    {
        // 执行用户自定制的逻辑
        std::cout << "id = " << id_ << std::endl;
    }

private:
    int id_;
};

int main()
{
    ThreadPool pool(10);
    
    for (int i = 0; i < 20; i++)
    {
        pool.AddTask(new MyTask(i));
    }

    while (1)
    {
        sleep(1);
    }
    return 0;
}

