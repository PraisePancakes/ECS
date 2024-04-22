#include <iostream>
#include <memory>
#include "../include/Manager/EntityManager.hpp"

int main(int argc, char *argv[])
{
    EntityManager em;
    Entity &e = em.AddEntity();
    Entity &e2 = em.AddEntity("Player");

    em.Update(); // call this in game loop first

    /*
        while(gameIsRunning) {
            em.Update();
            ...
            ...
            ...
        }

    */

    em.DisplayComponents();
    return 0;
}