#include "4-singleton.h"



Singleton *Singleton::instance = nullptr;

ThreadSafeSingleton *ThreadSafeSingleton::instance = nullptr;
std::mutex           ThreadSafeSingleton::mtx1;
std::mutex           ThreadSafeSingleton::mtx2;



int main()
{

    {
        debug(), "Testing Singleton:";
        auto s1 = Singleton::get();
        s1->someBusinessLogic();
        auto s2 = Singleton::get();
        s2->someBusinessLogic();
        debug(), "s1 and s2 are the same instance:", (s1 == s2);
    }


    {
        debug(), "Testing ThreadSafeSingleton:";
        auto ts1 = ThreadSafeSingleton::get();
        ts1->someBusinessLogic();
        auto ts2 = ThreadSafeSingleton::get();
        ts2->someBusinessLogic();
        debug(), "ts1 and ts2 are the same instance:", (ts1 == ts2);
    }

    {
        debug(), "==============================";
        debug(), "Testing SingletonTemplate with ThreadSafeSingleton:";
        auto st1 = SingletonTemplate<Logic1>::get();
        st1->someBusinessLogic();
        auto st2 = SingletonTemplate<Logic1>::get();
        st2->someBusinessLogic();
        debug(), "st1 and st2 are the same instance:", (st1 == st2);

        auto st3 = SingletonTemplate<Logic2>::get();
        st3->someBusinessLogic();
        auto st4 = SingletonTemplate<Logic2>::get();
        st4->someBusinessLogic();
        debug(), "st3 and st4 are the same instance:", (st3 == st4);
    }

    {
        debug(), "==============================";
        debug(), "Testing LazySingleton with Logic1:";
        auto ls1 = LazySingleton<Logic1>().get();
        ls1->someBusinessLogic();
        auto ls2 = LazySingleton<Logic1>().get();
        ls2->someBusinessLogic();
        debug(), "ls1 and ls2 are the same instance:", (ls1 == ls2);

        auto ls3 = LazySingleton<Logic2>().get();
        ls3->someBusinessLogic();
        auto ls4 = LazySingleton<Logic2>().get();
        ls4->someBusinessLogic();
        debug(), "ls3 and ls4 are the same instance:", (ls3 == ls4);
    }

    return 0;
}