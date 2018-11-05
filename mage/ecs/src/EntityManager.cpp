#include "ecs/EntityManager.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

namespace
{

// ------------------------------------------------------------------------------

constexpr std::int32_t c_invalidId = -1;

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

EntityManager::EntityManager()
    : m_freeEntityIds()
    , m_entityComponentMasks()
{
  m_freeEntityIds.reserve(1024);
  m_entityComponentMasks.reserve(1024);
}

// ------------------------------------------------------------------------------

Entity EntityManager::CreateEntity()
{
  std::int32_t entityId = 0;

  if (m_freeEntityIds.size() > 0)
  {
    entityId = m_freeEntityIds.back();
    m_freeEntityIds.pop_back();
  }
  else
  {
    entityId = static_cast<std::int32_t>(m_entityComponentMasks.size());
    m_entityComponentMasks.emplace_back();
  }

  return Entity(entityId);
}

// ------------------------------------------------------------------------------

void EntityManager::RecycleEntity(Entity& _entity)
{
  assert(_entity.m_id >= 0);
  m_freeEntityIds.emplace_back(_entity.m_id);
  _entity.m_id = c_invalidId;
}

// ------------------------------------------------------------------------------

ComponentMask EntityManager::GetComponentMaskForEntity(Entity _entity) const
{
  assert(_entity.m_id >= 0);
  return m_entityComponentMasks[_entity.m_id];
}

// ------------------------------------------------------------------------------

void EntityManager::ResetComponentMask(Entity _entity) noexcept
{
  assert(_entity.m_id >= 0);
  m_entityComponentMasks[_entity.m_id].Reset();
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage