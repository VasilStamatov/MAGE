#pragma once

#include <audio/AudioDevice.h>
#include <core/World.h>

class MainWorld : public mage::core::World
{
public:
  MainWorld(mage::core::Application& _application);

private:
  virtual void AddSystems() override;

  virtual void AddEntitiesAndComponents() override;
};