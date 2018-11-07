#pragma once

#include "System.h"

#include <memory>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class SystemManager
{
public:
  SystemManager();

  // ------------------------------------------------------------------------------

  void AddSystem(std::unique_ptr<System> _system);

  // ------------------------------------------------------------------------------

  void InitializeSystems(World& _world);
  void UninitializeSystems(World& _world);
  void TickSystems(World& _world, float _deltaTime);

  // ------------------------------------------------------------------------------

  void OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask);

  // ------------------------------------------------------------------------------

private:
  std::vector<std::unique_ptr<System>> m_systems;
};

} // namespace ecs
} // namespace mage