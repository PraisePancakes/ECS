#include "../include/Component.hpp"

Component::Component(ComponentTypeID id)
{
    this->m_typeID = id;
};

ComponentTypeID Component::GetComponentTypeID()
{
    static ComponentTypeID lastTypeID = 0;
    return lastTypeID++;
};

Entity *Component::GetOwner() const
{
    return this->entity;
}

[[nodiscard]] ComponentTypeID Component::GetTypeID() const
{
    return this->m_typeID;
};

Component::~Component(){};