#include "demo/CameraControlSystem.h"

#include <ecs/World.h>
#include <ecs_common/CameraComponent.h>
#include <input/InputManager.h>
#include <messaging/MessageBus.h>

CameraControlSystem::CameraControlSystem()
{
  m_systemSignature.AddComponent<mage::ecs::common::CameraComponent>();
  m_systemSignature.AddComponent<CameraControlComponent>();
}

void CameraControlSystem::Initialize(mage::ecs::World& _world)
{
  auto& appMsgBus = _world.GetApplicationMessageBus();

  appMsgBus.Subscribe(this, &CameraControlSystem::OnKeyPress);
  appMsgBus.Subscribe(this, &CameraControlSystem::OnKeyRelease);
  appMsgBus.Subscribe(this, &CameraControlSystem::OnMouseMove);
}

void CameraControlSystem::Tick(mage::ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& cameraComponent =
        _world.GetComponent<mage::ecs::common::CameraComponent>(entity);

    auto& camera = _world.GetCamera(cameraComponent.m_cameraId);

    mage::math::Quatf orientation = mage::math::Quatf::GenRotationX(m_pitch) *
                                    mage::math::Quatf::GenRotationY(m_yaw);

    camera.SetRotation(orientation);

    // mage::math::Vec3f forwardDir = mage::math::Quatf::RotateVec(
    //     orientation, mage::math::Vec3f(0.0f, 0.0f, -1.0f));
    // mage::math::Vec3f rightDir = mage::math::Quatf::RotateVec(
    //     orientation, mage::math::Vec3f(1.0f, 0.0f, 0.0f));
    // mage::math::Vec3f upDir = mage::math::Vec3f(0.0f, 1.0f, 0.0f);

    // mage::math::Vec3f accumMove =
    //     (forwardDir * m_forward) + (rightDir * m_right) + (upDir * m_up);

    camera.Translate(mage::math::Vec3f(m_right, m_up, -m_forward));
  }
}

void CameraControlSystem::OnKeyPress(mage::input::OnKeyPress* _event)
{
  if (_event->m_key == mage::input::InputKey::W)
  {
    m_forward = mage::math::Clamp(m_forward + 1.0f, -1.0f, 1.0f);
  }
  if (_event->m_key == mage::input::InputKey::S)
  {
    m_forward = mage::math::Clamp(m_forward - 1.0f, -1.0f, 1.0f);
  }

  if (_event->m_key == mage::input::InputKey::A)
  {
    m_right = mage::math::Clamp(m_right - 1.0f, -1.0f, 1.0f);
  }
  if (_event->m_key == mage::input::InputKey::D)
  {
    m_right = mage::math::Clamp(m_right + 1.0f, -1.0f, 1.0f);
  }

  if (_event->m_key == mage::input::InputKey::Q)
  {
    m_up = mage::math::Clamp(m_up - 1.0f, -1.0f, 1.0f);
  }
  if (_event->m_key == mage::input::InputKey::E)
  {
    m_up = mage::math::Clamp(m_up + 1.0f, -1.0f, 1.0f);
  }
}

void CameraControlSystem::OnKeyRelease(mage::input::OnKeyRelease* _event)
{
  if (_event->m_key == mage::input::InputKey::W)
  {
    m_forward = mage::math::Clamp(m_forward - 1.0f, -1.0f, 1.0f);
  }
  if (_event->m_key == mage::input::InputKey::S)
  {
    m_forward = mage::math::Clamp(m_forward + 1.0f, -1.0f, 1.0f);
  }

  if (_event->m_key == mage::input::InputKey::A)
  {
    m_right = mage::math::Clamp(m_right + 1.0f, -1.0f, 1.0f);
  }
  if (_event->m_key == mage::input::InputKey::D)
  {
    m_right = mage::math::Clamp(m_right - 1.0f, -1.0f, 1.0f);
  }

  if (_event->m_key == mage::input::InputKey::Q)
  {
    m_up = mage::math::Clamp(m_up + 1.0f, -1.0f, 1.0f);
  }
  if (_event->m_key == mage::input::InputKey::E)
  {
    m_up = mage::math::Clamp(m_up - 1.0f, -1.0f, 1.0f);
  }
}

void CameraControlSystem::OnMouseMove(
    mage::input::CursorPositionMovedEvent* _event)
{
  if (m_lastMouseX == 0.0f && m_lastMouseY == 0.0f)
  {
    m_lastMouseX = _event->m_xPos;
    m_lastMouseY = _event->m_yPos;
  }

  float deltaXMouse = 0.002f * (_event->m_xPos - m_lastMouseX);
  float deltaYMouse = 0.002f * (_event->m_yPos - m_lastMouseY);

  m_yaw += deltaXMouse;
  m_pitch += deltaYMouse;

  // printf("[m_yaw: %.3f] [m_pitch: %.3f]\n", m_yaw, m_pitch);

  m_lastMouseX = _event->m_xPos;
  m_lastMouseY = _event->m_yPos;
}