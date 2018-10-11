#pragma once

#include "Entity.h"

#include <algorithm>
#include <vector>

namespace mage
{
namespace ecs
{

template <typename ComponentType>
class ComponentManager
{
    struct ComponentData
    {
        Entity m_owner;
        ComponentType m_data;
    };

  private:
    std::vector<ComponentData> m_components;

  public:
    ComponentManager() : m_components()
    {
        m_components.reserve(1024);
    }

    template <typename... TArgs>
    void AddComponent(Entity _entity, TArgs &&... _constructionArgs)
    {
        if (FindComponentInstanceByEntity(_entity) != m_entityToComponentIdInVector.end())
        {
            //component already exists for this entity
            return;
        }

        m_components.emplace_back(_entity, std::forward<TArgs>(_constructionArgs)...);
    }

    void RemoveComponent(Entity _entity)
    {
        auto foundIterator = FindComponentInstanceByEntity(_entity);
        if (foundIterator == m_entityToComponentIdInVector.end())
        {
            //component doesn't exists for this entity
            return;
        }

        std::swap(foundIterator, m_components.back());
        m_components.pop_back();
    }

    ComponentType *GetComponent(Entity _entity)
    {
        ComponentType *ptrToComponent = nullptr;

        if (auto foundIterator = FindComponentInstanceByEntity(_entity);
            foundIterator != m_entityToComponentIdInVector.end())
        {
            //component already exists for this entity
            ptrToComponent = &foundIterator->m_data;
        }

        return ptrToComponent;
    }

  private:
    auto FindComponentInstanceByEntity(Entity _entity)
    {
        return std::find(m_components.begin(), m_components.end(), [_entity](const ComponentData &_element) {
            return _element.m_owner == _entity;
        });
    }
};

} // namespace ecs
} // namespace mage