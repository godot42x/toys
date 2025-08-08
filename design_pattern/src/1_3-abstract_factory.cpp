#include "helper.h"

struct IDoor {
    virtual ~IDoor() = default; // Ensure proper cleanup of derived classes

    virtual fn getDescription() -> const char * = 0;
};

struct WoodenDoor : IDoor {

    fn getDescription() -> const char * override { return "Wooden Door"; }
};

struct IronDoor : IDoor {


    fn getDescription() -> const char * override { return "Iron Door"; }
};

//-----------------------------------

struct IDoorFittingExpert {
    virtual ~IDoorFittingExpert() = default; // Ensure proper cleanup of derived classes

    virtual fn getFitting() -> const char * = 0;
};

// 木匠
struct Carpenter : IDoorFittingExpert {
    fn getFitting() -> const char * override { return "Wooden Door Fitting Expert"; }
};

// 焊接工
struct Welder : IDoorFittingExpert {
    fn getFitting() -> const char * override { return "Iron Door Fitting Expert"; }
};


//---------------------------------------------------

struct IDoorFactory {
    virtual fn makeDoor() -> IDoor                       * = 0;
    virtual fn makeFittingExpert() -> IDoorFittingExpert * = 0;
};

struct WoodenDoorFactory : IDoorFactory {
    fn makeDoor() -> IDoor * override { return new WoodenDoor(); }
    fn makeFittingExpert() -> IDoorFittingExpert * override { return new Carpenter(); }
};
struct IronDoorFactory : IDoorFactory {
    fn makeDoor() -> IDoor * override { return new IronDoor(); }
    fn makeFittingExpert() -> IDoorFittingExpert * override { return new Welder(); }
};

auto main() -> int
{
    auto factory = WoodenDoorFactory();
    auto door    = factory.makeDoor();
    auto expert  = factory.makeFittingExpert();
    debug(), door->getDescription(), "->", expert->getFitting();

    delete door;
    delete expert;

    auto factory2 = IronDoorFactory();
    auto door2    = factory2.makeDoor();
    auto expert2  = factory2.makeFittingExpert();
    debug(), door2->getDescription(), "->", expert2->getFitting();
    return 0;
}