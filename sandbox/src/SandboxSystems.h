#pragma once

#include "SandboxComponents.h"

#include <core/Application.h>
#include <ecs/World.h>
#include <input/InputManager.h>
#include <messaging/MessageBus.h>

class TestSystem : public mage::ecs::System
{
public:
  TestSystem() { m_systemSignature.AddComponent<SandboxComponent>(); }

  void Initialize(mage::ecs::World& _world)
  {
    auto& appMsgBus = _world.GetApplicationMessageBus();
    mage::input::AddBindingEvent binding;
    binding.m_key = mage::input::InputKey::Escape;
    binding.m_callback = [&appMsgBus]() {
      mage::core::OnExitAppEvent exitEvent;
      appMsgBus.Broadcast(&exitEvent);
    };

    appMsgBus.Broadcast(&binding);
  }

  void Tick(mage::ecs::World& _world, float _deltaTime) override
  {
    for (auto&& entity : m_registeredEntities)
    {
      auto testComponent = _world.GetComponent<SandboxComponent>(entity);
    }
  }
};