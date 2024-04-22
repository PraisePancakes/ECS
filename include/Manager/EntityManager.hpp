#pragma once
#include "../ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include <vector>
#include <memory>
#include <map>

typedef std::vector<std::unique_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector m_Entites;
    EntityMap m_EntityMap;
    std::size_t m_TotalEntites = 0;

public:
    EntityManager(){};
    Entity &AddEntity()
    {
        Entity *e = new Entity();
        std::unique_ptr<Entity> eUPtr{e};
        this->m_Entites.push_back(std::move(eUPtr));
        m_TotalEntites++;
        return *e;
    };

    Entity &AddEntity(const std::string &tag)
    {
        Entity *e = new Entity(tag);
        std::unique_ptr<Entity> eUPtr{e};
        this->m_Entites.push_back(std::move(eUPtr));
        m_TotalEntites++;
        return *e;
    };

    void Destroy()
    {
        for (auto &e : m_Entites)
        {
            if (!e->IsActive())
            {
                e = nullptr;
            }
        }
    };

    void DisplayComponents() const
    {
        for (size_t i = 0; i < m_Entites.size(); i++)
        {
            m_Entites[i]->DisplayComponents();
        }
    };

    // EntityVector &GetEntities(){};
    // EntityVector &GetEntities(const std::string &tag){};

    ~EntityManager(){};
};