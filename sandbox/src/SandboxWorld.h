#pragma once

#include "SandboxSystems.h"

#include <core/Application.h>

class SandboxWorld : public mage::ecs::World
{
public:
  SandboxWorld(mage::core::Application* _ownerApp)
      : mage::ecs::World(_ownerApp)
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