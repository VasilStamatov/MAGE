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
        std::uint32_t m_entityId;
        ComponentType m_data;

        ComponentData(std::uint32_t _entityId, const ComponentType &_data)
            : m_entityId(_entityId), m_data(_data)
        {
        }
    };

  private:
    std::vector<ComponentData> m_components;

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

        m_components.emplace_back(_entity.m_iD, _componentData);
    }

    void RemoveComponent(Entity _entity)
    {
        for (size_t i = 0; i < m_components.size(); i++)
        {
            if (m_components[i].m_entityId == _entity.m_iD)
            {
                std::swap(m_components[i], m_components.back());
                m_components.pop_back();
                return;
            }
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

  private:
    auto FindComponentInstanceByEntity(Entity _entity) noexcept
    {
        return std::find_if(m_components.begin(), m_components.end(), [_entity](const ComponentData &_element) {
            return _element.m_entityId == _entity.m_iD;
        });
    }
};

} // namespace ecs
} // namespace mage