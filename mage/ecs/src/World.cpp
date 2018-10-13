#include "ecs/World.h"

namespace mage
{
namespace ecs
{

void World::OnEnter()
{
    m_systemManager.InitializeSystems();
}

void World::OnExit()
{
    m_systemManager.UninitializeSystems();
}

EntityHandle World::CreateEntity()
{
    return EntityHandle(*this, m_entityManager.CreateEntity());
}

void World::DestroyEntity(Entity _entity)
{
    ComponentMask mask = m_entityManager.GetComponentMaskForEntity(_entity);

    for (size_t i = 0; i < 32; i++)
    {
        if (mask.HasComponent(i))
        {
            m_componentManagers[i]->RemoveComponent(_entity);
        }
    }

    m_entityManager.ResetComponentMask(_entity);

    m_systemManager.OnEntityComponentMaskChange(_entity, m_entityManager.GetComponentMaskForEntity(_entity));

    m_entityManager.RecycleEntity(_entity);
}

void World::AddSystem(std::unique_ptr<System> _system)
{
    m_systemManager.AddSystem(std::move(_system));
}

void World::TickSystems(float _deltaTime)
{
    m_systemManager.TickSystems(_deltaTime);
}

} // namespace ecs
} // namespace mage