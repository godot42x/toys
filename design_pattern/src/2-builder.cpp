#include "helper.h"



struct Burger {
    virtual ~Burger() = default;

    float size;

    bool bCheese    = false;
    bool bPepperoni = false; // 意大利辣香肠
    bool bLettuce   = false; // 生菜
    bool bTomato    = false; // 西红柿
};


struct BurgerBuilder {
    float size;

    bool bCheese    = false;
    bool bPepperoni = false; // 意大利辣香肠
    bool bLettuce   = false; // 生菜
    bool bTomato    = false; // 西红柿

    BurgerBuilder(float s) : size(s) {}
    BurgerBuilder &addCheese()
    {
        bCheese = true;
        return *this;
    }
    BurgerBuilder &addPepperoni()
    {
        bPepperoni = true;
        return *this;
    }
    BurgerBuilder &addLettuce()
    {
        bLettuce = true;
        return *this;
    }
    BurgerBuilder &addTomato()
    {
        bTomato = true;
        return *this;
    }

    Burger build()
    {
        Burger b;
        b.size       = size;
        b.bCheese    = bCheese;
        b.bPepperoni = bPepperoni;
        b.bLettuce   = bLettuce;
        b.bTomato    = bTomato;
        return b;
    }
};


int main(int argc, char **argv)
{
    auto burger = BurgerBuilder(10.0f)
                      .addCheese()
                      .addPepperoni()
                      .addLettuce()
                      .addTomato()
                      .build();

    debug(), "Burger size:", burger.size;
    debug(), "Has cheese:", burger.bCheese;
    debug(), "Has pepperoni:", burger.bPepperoni;
    debug(), "Has lettuce:", burger.bLettuce;
    debug(), "Has tomato:", burger.bTomato;

    return 0;
}