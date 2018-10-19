#pragma once

#include "ComponentMask.h"
#include "Entity.h"

#include <assert.h>
#include <vector>

namespace mage
{
namespace ecs
{

class EntityManager
{
public:
  EntityManager();

  Entity CreateEntity();
  void RecycleEntity(Entity& _entity);

  ComponentMask GetComponentMaskForEntity(Entity _entity) const;

  template <typename ComponentType> void AddComponent(Entity _entity) noexcept
  {
    assert(_entity.m_id >= 0);
    m_entityComponentMasks[_entity.m_id].AddComponent<ComponentType>();
  }

  template <typename ComponentType>
  void RemoveComponent(Entity _entity) noexcept
  {
    assert(_entity.m_id >= 0);
    m_entityComponentMasks[_entity.m_id].RemoveComponent<ComponentType>();
  }

  void ResetComponentMask(Entity _entity) noexcept;

private:
  std::vector<std::int32_t> m_freeEntityIds;
  std::vector<ComponentMask> m_entityComponentMasks;
};

} // namespace ecs
} // namespace mage