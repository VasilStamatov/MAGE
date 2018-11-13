#pragma once

#include <ecs/World.h>

class GameWorld : public mage::ecs::World
{
public:
  GameWorld(mage::messaging::MessageBus& _applicationMessageBus);

private:
  virtual void AddSystems() override;

  virtual void AddEntitiesAndComponents() override;
};