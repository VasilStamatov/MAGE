#pragma once

#include "SandboxSystems.h"

#include <messaging/MessageBus.h>

class SandboxWorld : public mage::ecs::World
{
public:
  SandboxWorld(mage::messaging::MessageBus& _applicationMessageBus)
      : mage::ecs::World(_applicationMessageBus)
  {
  }

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