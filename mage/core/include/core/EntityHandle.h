#pragma once

#include "ecs/Entity.h"

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

class World;

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// An EntityHandle is used to give a more OOP-looking interface to an entity
/// when an entity is created. It stores the entity Id and the world it was
/// created in to be able to add and remove components through the world.
/////////////////////////////////////////////////
class EntityHandle
{
public:
  EntityHandle(World& _world, ecs::Entity _entity);

  // ------------------------------------------------------------------------------

  void Destroy();

  // ------------------------------------------------------------------------------

  template <typename ComponentType, typename... TArgs>
  ComponentType& AddComponent(TArgs&&... _constructionArgs)
  {
    return m_world.AddComponent<ComponentType>(
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
  ecs::Entity m_entity;
};

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage