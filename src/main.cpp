#include <iostream>
#include <memory>
#include "../include/Manager/EntityManager.hpp"

int main(int argc, char *argv[])
{
    EntityManager em;
    Entity &e = em.AddEntity();
    Entity &e2 = em.AddEntity("Player");

    TransformComponent c = e2.AddComponent<TransformComponent>();

    em.Update(); // call this in game loop

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