#pragma once

#include "Entity.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class World;

// ------------------------------------------------------------------------------

class EntityHandle
{
public:
  EntityHandle(World& _world, Entity _entity);

  // ------------------------------------------------------------------------------

  void Destroy();

  // ------------------------------------------------------------------------------

  template <typename ComponentType, typename... TArgs>
  void AddComponent(TArgs&&... _constructionArgs)
  {
    m_world.AddComponent<ComponentType>(
        m_entity, std::forward<TArgs>(_constructionArgs)...);
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> void RemoveComponent()
  {
    m_world.RemoveComponent<ComponentType>(m_entity);
  }

  // ------------------------------------------------------------------------------

private:
  World& m_world;
  Entity m_entity;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage