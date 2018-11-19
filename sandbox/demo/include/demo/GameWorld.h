#pragma once

#include <audio/AudioDevice.h>
#include <ecs/World.h>

class GameWorld : public mage::ecs::World
{
public:
  GameWorld(mage::core::Application& _application);

private:
  virtual void AddSystems() override;

  virtual void AddEntitiesAndComponents() override;

private:
  mage::audio::AudioDevice& m_audioDevice;
};