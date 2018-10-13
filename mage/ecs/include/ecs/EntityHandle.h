#pragma once

#include "Entity.h"

namespace mage
{
namespace ecs
{

class World;

class EntityHandle
{
private:
  World &m_world;
  const Entity m_entity;

public:
  EntityHandle(World &_world, Entity _entity);

  void Destroy();

  template <typename ComponentType>
  void AddComponent(const ComponentType &_component)
  {
    m_world.AddComponent<ComponentType>(m_entity, _component);
  }

  template <typename ComponentType>
  void RemoveComponent()
  {
    m_world.RemoveComponent<ComponentType>(m_entity);
  }
};

} // namespace ecs
} // namespace mage