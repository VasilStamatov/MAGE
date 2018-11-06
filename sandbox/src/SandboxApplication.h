#pragma once

#include "SandboxWorld.h"

#include <core/Application.h>

class SandboxApplication : public mage::core::Application
{
private:
  virtual void AddGameWorlds() override
  {
    m_gameWorlds.push_back(
        std::make_unique<SandboxWorld>(m_applicationMessageBus));
  }
};