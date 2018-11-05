#pragma once

#include "SandboxSystems.h"

namespace me = mage::ecs;

class SandboxWorld : public me::World
{
private:
  virtual void AddSystems() override
  {
    AddSystem(std::make_unique<TestSystem>());
  }
  virtual void AddEntitiesAndComponents() override
  {
    auto handle = CreateEntity();
    handle.AddComponent<SandboxComponent>(1.0f, 1.0f, 1, 1, 1, 1);
  }
};