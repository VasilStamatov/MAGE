#pragma once

#include "Component.h"
#include "Entity.h"

#include <algorithm>
#include <assert.h>
#include <unordered_map>
#include <vector>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class BaseComponentManager
{
public:
  virtual void RemoveComponent(Entity _entity) = 0;
};

// ------------------------------------------------------------------------------

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

  // ------------------------------------------------------------------------------

public:
  ComponentManager()
      : m_entityIdToComponentIndex()
      , m_components()
  {
    m_components.reserve(64);
  }

  // ------------------------------------------------------------------------------

  template <typename... TArgs>
  ComponentType& AddComponent(Entity _entity, TArgs&&... _constructionArgs)
  {
    assert(m_entityIdToComponentIndex.count(_entity.m_id) == 0);

    m_components.emplace_back(std::forward<TArgs>(_constructionArgs)...);
    m_entityIdToComponentIndex[_entity.m_id] = m_components.size() - 1;
    return m_components.back();
  }

  // ------------------------------------------------------------------------------

  void RemoveComponent(Entity _entity) override
  {
    using std::swap;

    auto componentIndexToRemove = m_entityIdToComponentIndex[_entity.m_id];
    auto lastComponentIndex = m_components.size() - 1;

    swap(m_components[componentIndexToRemove],
         m_components[lastComponentIndex]);

    m_components.pop_back();

    for (auto&& entry : m_entityIdToComponentIndex)
    {
      if (entry.second == lastComponentIndex)
      {
        entry.second = componentIndexToRemove;
        break;
      }
    }

    m_entityIdToComponentIndex.erase(_entity.m_id);
  }

  // ------------------------------------------------------------------------------

  ComponentType* GetComponent(Entity _entity)
  {
    if (m_entityIdToComponentIndex.count(_entity.m_id) == 1)
    {
      // component exists
      return &m_components[m_entityIdToComponentIndex[_entity.m_id]];
    }
    return nullptr;
  }

  std::vector<ComponentType>& GetAllComponents() { return m_components; }

private:
  std::unordered_map<std::uint32_t, std::uint32_t> m_entityIdToComponentIndex;
  std::vector<ComponentType> m_components;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage