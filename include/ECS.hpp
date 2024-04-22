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

template <typename T> // a generic function that binds the static id to the type, rather than instance
ComponentTypeID GetComponentTypeID()
{
    static ComponentTypeID typeID = GetComponentTypeID();
    return typeID;
}

class Component // Clients can create their own components, as long as its inherited from the base component class
{
    ComponentTypeID m_typeID;

public:
    Entity *entity;
    /*
        @brief :
             This class is mainly responsible for assigning any derived component an ID and binding that derived component to an Entity instance.
             Any polymorphic methods are used to handle derived type methods that are required for that derived type to function.
             these polymorphic methods may not all be needed in the derived type, that is up to the client to implement for themselves, for this reason the methods will not be pure.


        @constructor-params :
                            the id will be passed using the GetComponentTypeID<T>() function. When creating your own derived component, the constructor of the derived component should pass
                            DerivedComponent() : Component(GetComponentTypeID<T>) {};,  where T = DerivedComponentType, to the base component constructor, this is crucial in giving component types a unique ID.

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
    virtual Component *Clone() const = 0;

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
                The max id value of any one entity is 4294967295.


*/

using EntityID = std::uint32_t;

class Entity
{
    friend class EntityManager;

    EntityID m_EntityID;
    std::vector<std::unique_ptr<Component>> m_Components;
    std::size_t m_CurrentComponentSize = 0;
    bool m_IsActive = true;
    std::string m_eTag = "Default";
    std::size_t genID()
    {
        static std::size_t lastID = 0;
        return lastID++;
    }

    Entity()
    {
        this->m_EntityID = genID();
    };

    Entity(const std::string &tag)
    {

        this->m_EntityID = genID();
        this->m_eTag = tag;
    };

public:
    void DisplayComponents() const
    {
        std::cout << "Entity    #" << this->m_EntityID << std::endl;
        std::cout << "Tag  " << this->m_eTag << std::endl;
        if (m_Components.size() == 0)
        {
            std::cout << "   contains no components " << std::endl;
            return;
        }

        for (auto &c : m_Components)
        {
            if (c != nullptr)
            {
                std::cout << "  Component    : " << typeid(*c).name() << std::endl;
                std::cout << "  Component ID : " << c->GetTypeID() << std::endl;
            }
        }
    };

    Entity &operator=(const Entity &rhs)
    {
        if (this != &rhs)
        {
            this->m_Components.clear();
            this->m_Components.reserve(rhs.m_Components.size());
            for (const auto &compPtr : rhs.m_Components)
            {

                if (compPtr)
                {
                    auto clone = std::unique_ptr<Component>(compPtr->Clone());
                    clone->entity = this;
                    this->m_Components.push_back(std::move(clone));
                }
            }
            this->m_CurrentComponentSize = this->m_Components.size();
            this->m_IsActive = rhs.m_IsActive;
            this->m_eTag = rhs.m_eTag;
        }
        return *this;
    }

    EntityID GetID() const { return this->m_EntityID; };

    std::string GetTag() const { return this->m_eTag; };
    /*
        @brief :
                The AddComponent generic method will accept any derived component from a base component class, and set the components entity ref owner to this instance

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

             maybe use an initialization list and forward the variadic args to the list

    */
    template <typename T>
    T &GetComponent()
    {
        ComponentTypeID typeID = GetComponentTypeID<T>();
        for (auto &c : m_Components)
        {
            if (c && c->GetTypeID() == typeID)
            {
                return (T &)*c;
            }
        }
        throw std::runtime_error("Component not found.");
    }

    template <typename T>
    T &AddComponent()
    {
        /*
            All components that will be bound to any one entity need to be limited to a single binding of that component type. To limit the number of bindings we can
            check if the Entity already has that component, if they do we just return the component at the component vector. The GetComponent<T>() template handles the retrieval of
            that bound component.

            @return :
                    the ownership is being moved to the components vector therefore we return a reference to that moved pointer, that way any modifications we make on the returned reference T
                    will also modify what is in the vector. For example, say we return from this function, lets look at the implementation..

                    TransformComponent c = someEntity.addComponent<TransformComponent>();

                    c.Translate(10, 5);
                    ^^^^^^^^^^^^^^^^^^^
                    this will modify the value stored at the TransformComponent's address in the entity's component vector.
                    this makes it much easier to just iterate and update all changed values of the components in the vector at once

        */
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
        /*
            When destroying an entity, all we need to do is set active = false, the actual deconstruction will be done when the EntityManager picks up a !isActive flag, in that case,
            we can remove the Entity from the manager and free the memory there.

        */
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

    ~Entity()
    {
        std::cout << "Entity with ID " << m_EntityID << " destroyed." << std::endl;
    };
};
