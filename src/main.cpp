#include <iostream>
#include <memory>
#include "../include/Manager/EntityManager.hpp"

int main(int argc, char *argv[])
{
    EntityManager em;
    Entity &e = em.AddEntity();
    Entity &e2 = em.AddEntity("Player");

    e2.AddComponent<TransformComponent>().GetPosition().AddPosition(5, 40);
    e.AddComponent<TransformComponent>();
    e.GetComponent<TransformComponent>().GetPosition().AddPosition(10.00, 15.00).Normalize();

    em.Update(); // call this in game loop first

    /*
        while(gameIsRunning) {
            em.Update();
            ...
            ...
            ...
        }

    */

    em.DisplayEntities();
    return 0;
}