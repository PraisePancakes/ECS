#include <iostream>
#include <memory>
#include "../include/Manager/EntityManager.hpp"

int main(int argc, char *argv[])
{
    EntityManager em;

    Entity &e = em.AddEntity("Player");
    Entity &e2 = em.AddEntity("Enemy");

    e2.AddComponent<SpriteComponent>();

    e2 = e;

    em.DisplayComponents();
    return 0;
}