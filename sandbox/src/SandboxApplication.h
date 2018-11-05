#pragma once

#include "SandboxWorld.h"

#include <core/Application.h>

namespace mc = mage::core;

class SandboxApplication : public mc::Application
{
public:
  virtual void AddGameWorlds() override
  {
    m_gameWorlds.push_back(std::make_unique<SandboxWorld>());
  }
};