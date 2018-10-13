#pragma once

#include "System.h"

#include <memory>

namespace mage
{
namespace ecs
{

class SystemManager
{
  private:
    std::vector<std::unique_ptr<System>> m_systems;

  public:
    SystemManager();

    void AddSystem(std::unique_ptr<System> _system);

    void InitializeSystems();
    void UninitializeSystems();

    void OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask);

    void TickSystems(float _deltaTime);
};

} // namespace ecs
} // namespace mage