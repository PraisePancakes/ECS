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
    [[nodiscard]] ComponentTypeID GetTypeID() const { return this->m_typeID; };
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

public:
    Entity()
    {
        static std::size_t lastID = 0;
        this->m_EntityID = lastID;
        lastID++;
    };

    void DisplayComponents() const
    {
        for (auto &c : m_Components)
        {
            if (c != nullptr)
            {
                std::cout << c->GetTypeID() << std::endl;
            }
        }
    };

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
    [[nodiscard]] T &AddComponent()
    {
        T *c = new T();
        c->entity = this;
        std::unique_ptr<T> cUPtr{c};
        this->m_Components.push_back(std::move(cUPtr));
        return *c;
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

class SpriteComponent : public Component
{

public:
    SpriteComponent() : Component(GetComponentTypeID<SpriteComponent>()) { std::cout << "Sprite Component Constructed " << GetComponentTypeID<SpriteComponent> << std::endl; };
    void Update() override{};
    void Render() override{};
    void Init() override{};
    ~SpriteComponent() override{};
};

class TransformComponent : public Component
{
    float xPos;
    float yPos;

public:
    TransformComponent() : Component(GetComponentTypeID<TransformComponent>()){};

    void Translate(float dX, float dY) noexcept
    {
        this->xPos += dX;
        this->yPos += dY;
    };
    void Update() override{};
    void Init() override{};
    void Render() override{};

    ~TransformComponent() override{};
};