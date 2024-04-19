#include "../include/Entity.hpp"

std::size_t MAX_COMPONENTS = 10; // if needed this may be changed for scalability (more component implementations than current set)

Entity::Entity()
{
    static std::size_t lastID = 0;
    this->m_EntityID = lastID;
    lastID++;
};