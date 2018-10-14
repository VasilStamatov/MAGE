#pragma once

#include "Component.h"
#include "Entity.h"

#include <algorithm>
#include <vector>

namespace mage
{
namespace ecs
{

class BaseComponentManager
{
  public:
    virtual void RemoveComponent(Entity _entity) = 0;
};

template <typename ComponentType>
class ComponentManager : public BaseComponentManager
{
    static_assert(std::is_base_of<Component, ComponentType>::value, "Must inherit from Component");
    static_assert(std::is_standard_layout<ComponentType>::value, "Must have standard layout (all members public, no virtual functions)");

    struct ComponentData
    {
        Entity m_ownerEntity;
        ComponentType m_data;

        ComponentData(Entity _entity, const ComponentType &_data)
            : m_ownerEntity(_entity), m_data(_data)
        {
        }
    };

  private:
    std::vector<ComponentData> m_components;

    auto FindComponentInstanceByEntity(Entity _entity)
    {
        return std::find_if(m_components.begin(), m_components.end(), [_entity](const ComponentData &_element) {
            return _element.m_ownerEntity == _entity;
        });
    }

  public:
    ComponentManager() : m_components()
    {
        m_components.reserve(1024);
    }

    void AddComponent(Entity _entity, const ComponentType &_componentData)
    {
        if (FindComponentInstanceByEntity(_entity) != m_components.end())
        {
            //component already exists for this entity
            return;
        }

        m_components.emplace_back(_entity, _componentData);
    }

    void RemoveComponent(Entity _entity) override
    {
        auto foundIterator = FindComponentInstanceByEntity(_entity);
        if (foundIterator != m_components.end())
        {
            m_components.erase(foundIterator);
        }
    }

    ComponentType *GetComponent(Entity _entity)
    {
        ComponentType *ptrToComponent = nullptr;

        auto foundIterator = FindComponentInstanceByEntity(_entity);
        if (foundIterator != m_components.end())
        {
            //component already exists for this entity
            ptrToComponent = &foundIterator->m_data;
        }

        return ptrToComponent;
    }
};

} // namespace ecs
} // namespace mage