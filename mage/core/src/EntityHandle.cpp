#include "core/EntityHandle.h"

#include "core/World.h"

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

EntityHandle::EntityHandle(World& _world, ecs::Entity _entity)
    : m_world(_world)
    , m_entity(_entity)
{
}

// ------------------------------------------------------------------------------

void EntityHandle::Destroy() { m_world.DestroyEntity(m_entity); }

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage