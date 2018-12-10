#include "demo/CameraControlSystem.h"

#include <audio/SoundEffectSystem.h>
#include <core/Application.h>
#include <ecs_common/CameraComponent.h>
#include <ecs_common/TransformComponent.h>
#include <messaging/MessageBus.h>

CameraControlSystem::CameraControlSystem()
{
  m_systemSignature.AddComponent<mage::ecs::common::CameraComponent>();
  m_systemSignature.AddComponent<mage::ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<CameraControlComponent>();
}

void CameraControlSystem::Initialize(mage::core::World& _world)
{
  auto& appMsgBus = _world.GetApplication().GetMessageBus();

  // appMsgBus.Subscribe(this, &CameraControlSystem::OnKeyPress);
  // appMsgBus.Subscribe(this, &CameraControlSystem::OnKeyRelease);
  appMsgBus.Subscribe(this, &CameraControlSystem::OnMouseMove);

  // Remove the cursor in fps mode
  mage::input::SetCursorStateEvent cursorState{
      mage::input::CursorState::Disabled};

  appMsgBus.Broadcast(&cursorState);
}

void CameraControlSystem::Tick(mage::core::World& _world, float _deltaSeconds)
{
  if (m_escapePressed)
  {
    mage::core::OnExitAppEvent exitApp;
    _world.GetApplication().GetMessageBus().Broadcast(&exitApp);
  }

  for (auto&& entity : m_registeredEntities)
  {
    auto* cameraControlComponent =
        _world.GetComponent<CameraControlComponent>(entity);
    auto* cameraComponent =
        _world.GetComponent<mage::ecs::common::CameraComponent>(entity);
    auto& transform =
        _world.GetComponent<mage::ecs::common::TransformComponent>(entity)
            ->m_transform;

    auto& camera =
        _world.GetRenderWorld().GetGameCamera(cameraComponent->m_cameraId);

    mage::math::Quatf orientation = (mage::math::Quatf::GenRotationX(m_pitch) *
                                     mage::math::Quatf::GenRotationY(m_yaw)) *
                                    cameraControlComponent->m_rotationSpeed;

    transform.SetRotation(orientation.GetConjugated());

    mage::math::Vec3f accumMove = (transform.GetForwardAxis() * m_forward) +
                                  (transform.GetRightAxis() * m_right) +
                                  (mage::math::Vec3f(0.0f, 1.0f, 0.0f) * m_up);

    transform.Translate(accumMove * cameraControlComponent->m_movementSpeed);

    camera.SetView(orientation.ToMat4() * mage::math::GenTranslationMat(
                                              transform.GetTranslation() * -1));

    if (m_playSoundPressed)
    {
      _world.AddComponent<mage::audio::PlaySoundEffect>(
          entity, _world.GetAudioWorld().GetSoundLibrary().GetAudioClip(
                      "./res/audio/Blip_Select11.ogg"));

      m_playSoundPressed = false;
    }
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

  if (_event->m_key == mage::input::InputKey::Escape)
  {
    m_escapePressed = true;
  }

  if (_event->m_key == mage::input::InputKey::Space)
  {
    m_playSoundPressed = true;
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

  float deltaXMouse = 0.005f * (_event->m_xPos - m_lastMouseX);
  float deltaYMouse = 0.005f * (_event->m_yPos - m_lastMouseY);

  m_yaw += deltaXMouse;
  m_pitch += deltaYMouse;

  // printf("[m_yaw: %.3f] [m_pitch: %.3f]\n", m_yaw, m_pitch);

  m_lastMouseX = _event->m_xPos;
  m_lastMouseY = _event->m_yPos;
}