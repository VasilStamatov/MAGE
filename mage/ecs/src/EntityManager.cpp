#include "ecs/EntityManager.h"

namespace mage
{
namespace ecs
{

EntityManager::EntityManager()
    : m_freeEntityIds(), m_lastFreeEntityId(0)
{
}

Entity EntityManager::CreateEntity()
{
    std::uint32_t entityId = 0;

    if (m_freeEntityIds.size() > 0)
    {
        entityId = m_freeEntityIds.front();
        m_freeEntityIds.pop();
    }
    else
    {
        entityId = m_lastFreeEntityId++;
    }

    return Entity(entityId);
}

void EntityManager::RecycleEntity(Entity _entity)
{
    m_freeEntityIds.push(_entity.m_iD);
}

} // namespace ecs
} // namespace mage