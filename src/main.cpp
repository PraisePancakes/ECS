#include <iostream>
#include "../include/ECS.hpp"
#include "../include/Manager/EntityManager.hpp"
#include <memory>

int main(int argc, char *argv[])
{
    EntityManager em;

    std::shared_ptr<Entity> e = em.addEntity();

    em.DisplayComponents();

    e->AddComponent<SpriteComponent>();

    e->AddComponent<TransformComponent>();

    em.DisplayComponents();

    return 0;
}