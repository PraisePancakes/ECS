#pragma once
#include "Entity.hpp"
#include <iostream>

using ComponentTypeID = std::size_t;
class Entity;
class Component
{
    ComponentTypeID m_typeID;

protected:
    ComponentTypeID GetComponentTypeID();
    template <typename T>
    ComponentTypeID GetComponentTypeID()
    {
        static ComponentTypeID typeID = GetComponentTypeID();
        return typeID;
    }

public:
    Entity *entity;
    /*
        @brief :
                type id will not be created in a component instance, but rather passed from a derived component class
                i.e
                DerivedComponent() : Component(GetComponentTypeID<DerivedComponent>) {};

    */
    Component(ComponentTypeID id);
    [[nodiscard]] ComponentTypeID GetTypeID() const;
    Entity *GetOwner() const;

    virtual void Init() = 0;
    virtual void Render() = 0;
    virtual void Update() = 0;

    virtual ~Component() = 0;
};