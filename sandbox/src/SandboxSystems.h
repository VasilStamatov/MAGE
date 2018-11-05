#pragma once

#include "SandboxComponents.h"

#include <ecs/World.h>

class TestSystem : public mage::ecs::System
{
public:
  TestSystem() { m_systemSignature.AddComponent<SandboxComponent>(); }

  void Tick(mage::ecs::World& _world, float _deltaTime) override
  {
    for (auto&& entity : m_registeredEntities)
    {
      auto testComponent = _world.GetComponent<SandboxComponent>(entity);
    }
  }
};