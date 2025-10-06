#pragma once

#include "helper.h"


struct Sheep {

    std::string name;
    std::string color;
    int         age;

    Sheep(std::string n, std::string c, int a) : name(n), color(c), age(a) {}
    Sheep(const Sheep &other) : name(other.name), color(other.color), age(other.age) {}


    std::string getName() const { return name; }
    void        setName(const std::string &name_) { name = name_; }

    std::string getColor() const { return color; }
    void        setColor(const std::string &color_) { color = color_; }

    int  getAge() const { return age; }
    void setAge(int age_) { age = age_; }


    fn clone() -> Sheep * { return new Sheep(*this); }
};