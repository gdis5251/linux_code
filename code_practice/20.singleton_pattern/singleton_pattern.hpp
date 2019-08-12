#pragma once
#include <iostream>
#include <mutex>

// 饿汉模式
class Hungry
{
public:
    static Hungry* GetInstance()
    {
        return &m_instance_;
    }
private:
    // 将构造函数私有
    Hungry()
    {}

    // 删除拷贝构造和赋值运算符重载
    // 防止该类被创建多份
    Hungry(const Hungry& instance) = delete;
    Hungry& operator=(const Hungry& instance) = delete;
    // 定义一个静态对象，在定义对象的时候就初始化
    static Hungry m_instance_;
};

Hungry Hungry::m_instance_;


// 懒汉模式
class Singleton
{
public:
    static Singleton* GetInstance()
    {
        if (m_instance_ == nullptr)
        {
            mutex_.lock();
            if (m_instance_ == nullptr)
            {
                m_instance_ = new Singleton();
            }
            mutex_.unlock();

            return m_instance_;

        }
    }

    class CGorbo
    {
    public:
        ~CGorbo()
        {
            if (Singleton::m_instance_ != nullptr)
            {
                delete m_instance_;
            }
        }
    };

private:
    Singleton() {}

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton) = delete;

    static volatile Singleton* m_instance_;
    static std::mutex mutex_;
    static CGorbo c_gorbo_;
};

volatile Singleton* Singleton::m_instance_ = nullptr;
std::mutex Singleton::mutex_;
Singleton::CGorbo cg;
