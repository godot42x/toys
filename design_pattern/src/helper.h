#pragma once
#include <iostream>

#define fn auto

struct debug final {
    std::ostream &os = std::cout;


    ~debug() { os << "\n"; }

    template <typename... Args>
    debug &operator,(Args &&...args)
    {
        (os << ... << args) << ' ';
        return *this;
    }

    template <typename T>
    debug &operator,(T &&v)
    {
        os << v << ' ';
        return *this;
    }
};
