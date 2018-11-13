#pragma once

#include "System.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class GameSystem : public System
{
public:
  GameSystem();
  virtual ~GameSystem();

  virtual void Tick(World& _world, float _deltaTime) = 0;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage