#include "ecs/SystemManager.h"

namespace mage
{
namespace ecs
{

SystemManager::SystemManager()
{
}

void SystemManager::AddSystem(std::unique_ptr<System> _system)
{
    m_systems.push_back(std::move(_system));
}

void SystemManager::InitializeSystems()
{
    for (auto &&system : m_systems)
    {
        system->Initialize();
    }
}

void SystemManager::UninitializeSystems()
{
    for (auto &&system : m_systems)
    {
        system->Uninitialize();
    }
}

void SystemManager::OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask)
{
    for (auto &&system : m_systems)
    {
        system->OnEntityComponentMaskChange(_entity, _newMask);
    }
}

void SystemManager::TickSystems(float _deltaTime)
{
    for (auto &&system : m_systems)
    {
        system->Tick(_deltaTime);
    }
}

} // namespace ecs
} // namespace mage