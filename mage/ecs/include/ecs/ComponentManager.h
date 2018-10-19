#pragma once

#include "Component.h"
#include "Entity.h"

#include <algorithm>
#include <assert.h>
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
  static_assert(std::is_base_of<Component, ComponentType>::value,
                "Must inherit from Component");
  static_assert(std::is_standard_layout<ComponentType>::value,
                "Members must be public, no virtual functions");
  static_assert(std::is_move_constructible<ComponentType>::value,
                "Must be move constructibe");
  static_assert(std::is_move_assignable<ComponentType>::value,
                "Must be move assignable");

public:
  ComponentManager()
      : m_components()
  {
    m_components.reserve(1024);
  }

  template <typename... TArgs>
  void AddComponent(Entity _entity, TArgs&&... _constructionArgs)
  {
    if (FindComponentInstanceByEntity(_entity) != m_components.end())
    {
      // component already exists for this entity
      return;
    }

    m_components.emplace_back(
        _entity, ComponentType(std::forward<TArgs>(_constructionArgs)...));
  }

  void RemoveComponent(Entity _entity) override
  {
    auto foundIterator = FindComponentInstanceByEntity(_entity);
    if (foundIterator != m_components.end())
    {
      m_components.erase(foundIterator);
    }
  }

  ComponentType& GetComponent(Entity _entity)
  {
    auto foundIterator = FindComponentInstanceByEntity(_entity);
    assert(foundIterator != m_components.end());
    return foundIterator->m_data;
  }

private:
  auto FindComponentInstanceByEntity(Entity _entity)
  {
    return std::find_if(m_components.begin(), m_components.end(),
                        [_entity](const ComponentInstance& _element) {
                          return _element.m_ownerEntity == _entity;
                        });
  }

private:
  struct ComponentInstance
  {
    Entity m_ownerEntity;
    ComponentType m_data;

    ComponentInstance(Entity _entity, ComponentType _data)
        : m_ownerEntity(_entity)
        , m_data(std::move(_data))
    {
    }
  };

  std::vector<ComponentInstance> m_components;
};

} // namespace ecs
} // namespace mage