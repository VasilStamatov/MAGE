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

  for (auto&& entity : m_registeredEntities)
  {
    auto& CameraControls = _world.GetComponent<CameraControlComponent>(entity);

    mage::input::AddBindingEvent forwardBind;

    forwardBind.m_key = mage::input::InputKey::W;
    forwardBind.m_callback = [&CameraControls]() {
      CameraControls.m_forward = -1.0f;
    };

    mage::input::AddBindingEvent backwardBind;

    backwardBind.m_key = mage::input::InputKey::S;
    backwardBind.m_callback = [&CameraControls]() {
      CameraControls.m_forward = 1.0f;
    };

    mage::input::AddBindingEvent rightBind;

    rightBind.m_key = mage::input::InputKey::D;
    rightBind.m_callback = [&CameraControls]() {
      CameraControls.m_right = 1.0f;
    };

    mage::input::AddBindingEvent leftBind;

    leftBind.m_key = mage::input::InputKey::A;
    leftBind.m_callback = [&CameraControls]() {
      CameraControls.m_right = -1.0f;
    };

    appMsgBus.Broadcast(&forwardBind);
    appMsgBus.Broadcast(&backwardBind);
    appMsgBus.Broadcast(&rightBind);
    appMsgBus.Broadcast(&leftBind);
  }
}

void CameraControlSystem::Tick(mage::ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& cameraControlComponent =
        _world.GetComponent<CameraControlComponent>(entity);
    auto& cameraComponent =
        _world.GetComponent<mage::ecs::common::CameraComponent>(entity);

    _world.GetCamera(cameraComponent.m_cameraId)
        .Translate(mage::math::Vec3f(cameraControlComponent.m_right, 0.0f,
                                     cameraControlComponent.m_forward));

    cameraControlComponent.m_forward = 0;
    cameraControlComponent.m_right = 0;
  }
}