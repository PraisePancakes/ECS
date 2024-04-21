#pragma once
#include "../ECS.hpp"
#include <vector>
#include <memory>
#include <map>

#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"

class Entity;
typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector m_Entites;
    EntityMap m_EntityMap;
    std::size_t m_TotalEntites = 0;

public:
    EntityManager(){};
    std::shared_ptr<Entity> addEntity()
    {
        std::shared_ptr<Entity> newEntity = std::make_unique<Entity>();
        m_Entites.push_back(newEntity);

        return newEntity;
    };

    void DisplayComponents() const
    {
        for (size_t i = 0; i < m_Entites.size(); i++)
        {
            m_Entites[i]->DisplayComponents();
        }
    };

    // std::unique_ptr<Entity> addEntity(const std::string &tag){};

    // EntityVector &GetEntities(){};
    // EntityVector &GetEntities(const std::string &tag){};

    ~EntityManager(){};
};