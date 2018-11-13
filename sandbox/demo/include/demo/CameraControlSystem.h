#pragma once

#include <ecs/GameSystem.h>

struct CameraControlComponent : public mage::ecs::Component
{
  float m_forward = 0.0f;
  float m_right = 0.0f;
};

class CameraControlSystem : public mage::ecs::GameSystem
{
public:
  CameraControlSystem();

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Tick(mage::ecs::World& _world, float _deltaTime) override;
};