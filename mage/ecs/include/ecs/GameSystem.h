#pragma once

#include "System.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The game system describes a system which is called every game state update,
/// which happens at a fixed rate.
/////////////////////////////////////////////////
class GameSystem : public System
{
public:
  GameSystem();
  virtual ~GameSystem();

  virtual void Initialize(core::World& _world) {}
  virtual void Uninitialize(core::World& _world) {}

  virtual void Tick(core::World& _world, float _deltaSeconds) = 0;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage