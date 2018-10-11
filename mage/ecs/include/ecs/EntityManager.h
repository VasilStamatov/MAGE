#pragma once

#include "Entity.h"

#include <queue>

namespace mage
{
namespace ecs
{

class EntityManager
{
private:
  std::queue<std::uint32_t> m_freeEntityIds;
  std::uint32_t m_lastFreeEntityId;

public:
  EntityManager();

  Entity CreateEntity();
  void RecycleEntity(Entity _entity);
};

} // namespace ecs
} // namespace mage