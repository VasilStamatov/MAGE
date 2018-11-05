#pragma once

#include "SandboxComponents.h"

#include <ecs/World.h>

namespace me = mage::ecs;

class TestSystem : public me::System
{
public:
  TestSystem() { m_systemSignature.AddComponent<SandboxComponent>(); }

  void Tick(me::World& _world, float _deltaTime) override
  {
    for (auto&& entity : m_registeredEntities)
    {
      auto testComponent = _world.GetComponent<SandboxComponent>(entity);
    }
  }
};