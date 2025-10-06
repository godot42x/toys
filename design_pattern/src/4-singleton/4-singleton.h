#pragma once

#include "../helper.h"


// NOTICE: static member variables must be defined in a .cpp file to avoid multiple definition errors.

template <typename T>
struct SingletonTemplate;

// MARK: classic
struct Singleton {
  private:
    static Singleton *instance;

    Singleton() { debug(), "Singleton Instance Created"; }

  public:
    Singleton(const Singleton &)            = delete;
    Singleton &operator=(const Singleton &) = delete;

    static fn get() -> Singleton *
    {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    fn someBusinessLogic() -> void { debug(), "Executing some business logic."; }
};


// MARK: thread safe
#include <mutex>

struct ThreadSafeSingleton {
  private:
    static ThreadSafeSingleton *instance;
    static std::mutex           mtx1;
    static std::mutex           mtx2;

    ThreadSafeSingleton() { debug(), "ThreadSafeSingleton Instance Created"; }

    // Allow SingletonTemplate to access private constructor
    friend struct SingletonTemplate<ThreadSafeSingleton>;

  public:
    ThreadSafeSingleton(const ThreadSafeSingleton &)            = delete;
    ThreadSafeSingleton &operator=(const ThreadSafeSingleton &) = delete;

    static fn get() -> ThreadSafeSingleton *
    {
        std::lock_guard<std::mutex> lock(mtx1);
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx2);
            instance = new ThreadSafeSingleton();
        }
        return instance;
    }

    fn someBusinessLogic() -> void { debug(), "Executing some business logic."; }
};



// MARK: templated
// but not thread safe
struct Logic1 {
    Logic1() { debug(), "Logic Instance Created"; }
    fn someBusinessLogic() -> void { debug(), "Executing some business logic."; }
};

struct Logic2 {
    Logic2() { debug(), "Logic2 Instance Created"; }
    fn someBusinessLogic() -> void { debug(), "Executing some business logic2."; }
};


template <typename T>
struct SingletonTemplate {
  private:
    static T         *instance;
    static std::mutex mtx;

    SingletonTemplate() { debug(), "SingletonTemplate Instance Created"; }

  public:
    SingletonTemplate(const SingletonTemplate &)            = delete;
    SingletonTemplate &operator=(const SingletonTemplate &) = delete;

    static fn get() -> T *
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new T();
        }
        return instance;
    }
};


template <typename T>
T *SingletonTemplate<T>::instance = nullptr;
template <typename T>
std::mutex SingletonTemplate<T>::mtx;



// MARK: lazy singleton
template <typename T>
struct LazySingleton {

    T *get()
    {
        // TODO: this will not be worked in cross dll boundary
        static T instance;
        return &instance;
    }
};