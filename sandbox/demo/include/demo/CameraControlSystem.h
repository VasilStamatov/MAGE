#pragma once

#include <ecs/GameSystem.h>
#include <input/InputManager.h>

struct CameraControlComponent : public mage::ecs::Component
{
  float m_movementSpeed = 1.0f;
  float m_rotationSpeed = 1.0f;
};

class CameraControlSystem : public mage::ecs::GameSystem
{
public:
  CameraControlSystem();

  virtual void Initialize(mage::core::World& _world) override;

  virtual void Tick(mage::core::World& _world, float _deltaSeconds) override;

private:
  void OnKeyPress(mage::input::OnKeyPress* _event);
  void OnKeyRelease(mage::input::OnKeyRelease* _event);
  void OnMouseMove(mage::input::CursorPositionMovedEvent* _event);

  float m_forward = 0.0f;
  float m_right = 0.0f;
  float m_up = 0.0f;

  float m_lastMouseX = 0.0f;
  float m_lastMouseY = 0.0f;

  float m_pitch = 0.0f;
  float m_yaw = 0.0f;

  bool m_escapePressed = false;
  bool m_playSoundPressed = false;
};