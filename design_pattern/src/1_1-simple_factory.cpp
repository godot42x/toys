#include "helper.h"

struct IDoor {
    virtual auto getWidth() -> float  = 0;
    virtual auto getHeight() -> float = 0;
};

struct WoodenDoor : IDoor {

    float width;
    float height;

    WoodenDoor(float w, float h) : width(w), height(h) {}

    auto getWidth() -> float override { return width; }
    auto getHeight() -> float override { return height; }
};

struct DoorFactory {
    static auto makeDoor(float width, float height) -> IDoor *
    {
        return new WoodenDoor(width, height);
    }
};

auto main() -> int
{
    auto door = DoorFactory::makeDoor(3.0f, 7.0f);
    debug(), door->getWidth(), door->getHeight();

    auto door2 = DoorFactory::makeDoor(4.0f, 8.0f);
    debug(), door2->getWidth(), door2->getHeight();
    return 0;
}