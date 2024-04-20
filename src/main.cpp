#include <iostream>
#include "../include/ECS.hpp"

int main(int argc, char *argv[])
{
    Entity e;
    SpriteComponent sc = e.AddComponent<SpriteComponent>();

    return 0;
}