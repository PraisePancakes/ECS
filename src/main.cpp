#include <iostream>
#include "../include/Entity.hpp"
#include "../include/Component.hpp"
#include "../include/TransformComponent.hpp"

int main(int argc, char *argv[])
{
    Entity e;
    e.AddComponent<TransformComponent>();
    e.DisplayComponents();

    return 0;
}