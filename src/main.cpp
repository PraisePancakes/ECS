#include <iostream>
#include "../include/Entity.hpp"
#include "../include/Component.hpp"
#include "../include/TransformComponent.hpp"

int main(int argc, char *argv[])
{
    TransformComponent tc;
    ComponentTypeID id = tc.GetTypeID();
    std::cout << id;
    return 0;
}