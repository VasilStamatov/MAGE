#include "ecs/EntityManager.h"

namespace mage
{
namespace ecs
{

EntityManager::EntityManager()
    : m_freeEntityIds(), m_entityComponentMasks(0)
{
}

Entity EntityManager::CreateEntity()
{
    std::uint32_t entityId = 0;

    if (m_freeEntityIds.size() > 0)
    {
        entityId = m_freeEntityIds.back();
        m_freeEntityIds.pop_back();
    }
    else
    {
        entityId = m_entityComponentMasks.size();
        m_entityComponentMasks.emplace_back();
    }

    return Entity(entityId);
}

void EntityManager::RecycleEntity(Entity _entity)
{
    m_freeEntityIds.emplace_back(_entity.m_id);
}

ComponentMask EntityManager::GetComponentMaskForEntity(Entity _entity) const noexcept
{
    return m_entityComponentMasks[_entity.m_id];
}

void EntityManager::SetComponentBit(Entity _entity, std::uint32_t _componentBit) noexcept
{
    m_entityComponentMasks[_entity.m_id].SetComponentBit(_componentBit);
}

void EntityManager::UnsetComponentBit(Entity _entity, std::uint32_t _componentBit) noexcept
{
    m_entityComponentMasks[_entity.m_id].UnsetComponentBit(_componentBit);
}

void EntityManager::ResetComponentMask(Entity _entity) noexcept
{
    m_entityComponentMasks[_entity.m_id].Reset();
}

} // namespace ecs
} // namespace mage