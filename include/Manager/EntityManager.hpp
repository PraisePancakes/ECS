#pragma once
#include "../ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector m_Entites;
    EntityMap m_EntityMap;
    std::size_t m_TotalEntites = 0;
    EntityVector m_AddedEntities;

public:
    EntityManager(){};
    Entity &AddEntity()
    {
        auto e = std::shared_ptr<Entity>(new Entity());
        m_TotalEntites++;
        this->m_AddedEntities.push_back(e);
        return *e;
    };

    Entity &AddEntity(const std::string &tag)
    {
        auto e = std::shared_ptr<Entity>(new Entity(tag));
        m_TotalEntites++;
        this->m_AddedEntities.push_back(e);
        return *e;
    };

    void Update()
    {
        for (auto &e : m_AddedEntities)
        {
            m_Entites.push_back(e);
            m_EntityMap[e->GetTag()].push_back(e);
        }

        m_Entites.erase(std::remove_if(m_Entites.begin(), m_Entites.end(), [](const auto &e)
                                       { return !e->IsActive(); }),
                        m_Entites.end());

        m_AddedEntities.clear();
    };

    EntityVector &GetEntities()
    {
        return this->m_Entites;
    };

    EntityVector &GetEntities(const std::string &tag)
    {
        return this->m_EntityMap[tag];
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

    void DisplayEntities() const
    {
        for (size_t i = 0; i < m_Entites.size(); i++)
        {
            m_Entites[i]->DisplayEntity();
            if (m_Entites[i]->HasComponent<TransformComponent>())
            {
                m_Entites[i]->GetComponent<TransformComponent>().DisplayPosition();
            }
            std::cout << "\n"
                      << std::endl;
        }
    };

    ~EntityManager()
    {
        Destroy();
    };
};