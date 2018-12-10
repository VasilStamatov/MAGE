#pragma once

#include "GameSystem.h"

#include <memory>

namespace mage
{
namespace ecs
{

class GameWorld
{
public:
  GameWorld(core::World& _ownerWorld);
  ~GameWorld();

  // ------------------------------------------------------------------------------

  void Initialize();
  void Uninitialize();

  // ------------------------------------------------------------------------------

  void Tick(float _deltaSeconds);

  // ------------------------------------------------------------------------------

  void UpdateEntityStatus(ecs::Entity& _entity,
                          ecs::ComponentMask _entitySignature);

  // ------------------------------------------------------------------------------

  void AddGameSystem(std::unique_ptr<GameSystem> _system);

private:
  std::vector<std::unique_ptr<GameSystem>> m_gameSystems;

  core::World& m_ownerWorld;
};

} // namespace ecs
} // namespace mage