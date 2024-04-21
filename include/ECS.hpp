#pragma once
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>

class Entity;
class Component;
using ComponentTypeID = std::size_t;

ComponentTypeID GetComponentTypeID()
{
    static ComponentTypeID lastID = 0;
    return lastID++;
}

template <typename T>
ComponentTypeID GetComponentTypeID()
{
    static ComponentTypeID typeID = GetComponentTypeID();
    return typeID;
}

class Component
{
    ComponentTypeID m_typeID;

protected:
public:
    Entity *entity;
    /*
        @brief :
                type id will not be created in a component instance, but rather passed from a derived component class
                i.e
                DerivedComponent() : Component(GetComponentTypeID<DerivedComponent>) {};

    */
    Component(ComponentTypeID id)
    {
        this->m_typeID = id;
    };
    ComponentTypeID GetTypeID() const { return this->m_typeID; };
    Entity *GetOwner() const
    {
        return this->entity;
    };

    virtual void Init(){};
    virtual void Render(){};
    virtual void Update(){};

    virtual ~Component(){};
};

/*
@brief :
        What is an Entity? an entity will simply just be an ID and a set of components in this ecs, nothing more nothing less, entities are used to bind a set of components to one object.

@implementation :
        How would we implement an Entity? there are many ways to implement an entity however here is the general flow that I will be sticking with.

        1) Create an id for the entity...
            An id in this case will be a std::uint32_t integer for many reasons.
                i. this is an unsigned number meaning the entities id can never be negative, since the entity will be indexed in some sort of quick access table (Hash, look-up, etc...), it is important
                for the entity to not have a negative id because we will not be permitted to look up a negative index in any one table.

                ii. the max value of this unsigned integer is ~ 4294967295 meaning any engine that needs to incorporate such a large quantity of entities, can do just that.
                This also means that the max id value of any one entity is 4294967295.


*/

using EntityID = std::uint32_t;

class Entity
{
    EntityID m_EntityID;
    std::vector<std::unique_ptr<Component>> m_Components;
    std::size_t m_CurrentComponentSize = 0;
    bool m_IsActive = true;
    std::string m_eTag = "Default";

public:
    Entity()
    {
        static std::size_t lastID = 0;
        this->m_EntityID = lastID;
        lastID++;
    };

    Entity(const std::string &tag)
    {
        static std::size_t lastID = 0;
        this->m_EntityID = lastID;
        this->m_eTag = tag;
        lastID++;
    };

    void DisplayComponents() const
    {
        if (m_Components.size() == 0)
        {
            std::cout << "Entity contains no components " << std::endl;
            return;
        }
        for (auto &c : m_Components)
        {
            if (c != nullptr)
            {
                std::cout << "Component ID : " << c->GetTypeID() << std::endl;
            }
        }
    };

    EntityID GetID() const { return this->m_EntityID; };

    std::string GetTag() const { return this->m_eTag; };
    /*
        @brief :
                The AddComponent generic method will be accept any derived component from a base component class, and set the components entity ref owner to this instance

        @implementation :
                its return will be the component that was just added and can be modifiable, called like so..
                SomeComponent c = entity.AddComponent<SomeComponent>();
                c.doSomething();
                c.changeSomething();

                whatever changes with c will change in the entities component reference to c as well


        @template-params
                the template parametrics will be of some derived component type, e.g Transform, Sprite, RigidBody, Physics, etc...


            this template allows for a call like so :
             entity.AddComponent<SomeComponent>();

             TO-DO:
             implement variadics for this template function such that I can call multiple components to the AddComponent method
             e.g.

             entity.AddComponent<C1, C2,...CN>();

             maybe use an initialization_list and forward the variadic args to the list

    */
    template <typename T>
    T &GetComponent()
    {
        // Find and return the component of type T if it exists
        ComponentTypeID typeID = GetComponentTypeID<T>();
        for (auto &c : m_Components)
        {
            if (c && c->GetTypeID() == typeID)
            {
                return dynamic_cast<T &>(*c);
            }
        }
        // If component of type T does not exist, throw an exception or handle accordingly
        throw std::runtime_error("Component not found.");
    }

    template <typename T>
    T &AddComponent()
    {
        if (HasComponent<T>())
        {
            return GetComponent<T>();
        }
        T *c = new T();
        c->entity = this;
        std::unique_ptr<T> cUPtr{c};
        this->m_Components.push_back(std::move(cUPtr));
        m_CurrentComponentSize = m_Components.size();
        return *c;
    };

    bool IsActive() const
    {
        return m_IsActive;
    }

    void DestroyEntity()
    {
        this->m_IsActive = false;
    };

    template <typename T>
    bool HasComponent()
    {
        ComponentTypeID typeID = GetComponentTypeID<T>();
        if (typeID < m_Components.size() && m_Components[typeID] != nullptr)
        {
            return true;
        }
        return false;
    }

    ~Entity(){};
};
