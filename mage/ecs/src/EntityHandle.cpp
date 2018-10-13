#include "ecs/EntityHandle.h"

#include "ecs/World.h"

namespace mage
{
namespace ecs
{

EntityHandle::EntityHandle(World &_world, Entity _entity)
    : m_world(_world), m_entity(_entity)
{
}

void EntityHandle::Destroy()
{
    m_world.DestroyEntity(m_entity);
}

} // namespace ecs
} // namespace mage