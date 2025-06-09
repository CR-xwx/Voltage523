#pragma once

#include <mutex> 

template <class T>
class Singleton
{
public:
    template <typename... Args>
    static T *getInstance(Args &&...aArgs)
    {
        std::call_once(mFlag, [&]()
                       { mInstance = new T(std::forward<Args>(aArgs)...); });

        return mInstance;
    }

    static void destroyInstance(void)
    {
        if (nullptr != mInstance)
        {
            delete mInstance;
            mInstance = nullptr;
        }
    }

private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    static T *mInstance;
    static std::once_flag mFlag;
};

template <class T>
T *Singleton<T>::mInstance = nullptr;
template <class T>
std::once_flag Singleton<T>::mFlag;
