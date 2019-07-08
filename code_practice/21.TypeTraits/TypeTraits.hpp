#pragma once
#include <iostream>
#include <cstring>

// 表示内置类型
struct TrueType
{
    static bool Get()
    {
        return true;
    }
};

// 表示自定义类型
struct FalseType
{
    static bool Get()
    {
        return false;
    }
};

template <class T>
struct TypeTraits
{
    typedef FalseType IsPODType;
};

template <>
struct TypeTraits<int>
{
    typedef TrueType IsPODType;
};

template <>
struct TypeTraits<short>
{
    typedef TrueType IsPODType;
};

template <>
struct TypeTraits<long>
{
    typedef TrueType IsPODType;
};

template <>
struct TypeTraits<char>
{
    typedef TrueType IsPODType;
};

template <>
struct TypeTraits<double>
{
    typedef TrueType IsPODType;
};

template <class T>
void Copy(T& dest, const T& src, size_t size)
{
    if (TypeTraits<T>::IsPODType::Get())
    {
        memset(dest, src, size);      
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            dest[i] = src[i];
        }
    }
}
