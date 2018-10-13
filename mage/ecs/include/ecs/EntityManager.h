#pragma once

#include "ComponentMask.h"
#include "Entity.h"

#include <vector>

namespace mage
{
namespace ecs
{

class EntityManager
{
private:
  std::vector<std::uint32_t> m_freeEntityIds;
  std::vector<ComponentMask> m_entityComponentMasks;

public:
  EntityManager();

  Entity CreateEntity();
  void RecycleEntity(Entity _entity);

  ComponentMask GetComponentMaskForEntity(Entity _entity) const noexcept;

  void SetComponentBit(Entity _entity, std::uint32_t _componentBit) noexcept;
  void UnsetComponentBit(Entity _entity, std::uint32_t _componentBit) noexcept;
  void ResetComponentMask(Entity _entity) noexcept;
};

} // namespace ecs
} // namespace mage