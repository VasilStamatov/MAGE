#include "demo/GameCollisionHandler.h"

#include "demo/MovementControlSystem.h"

#include <audio/SoundEffectSystem.h>
#include <core/Application.h>
#include <ecs/World.h>
#include <messaging/MessageBus.h>
#include <physics/MotionSystem.h>

// ------------------------------------------------------------------------------

GameCollisionhandler::GameCollisionhandler() {}

// ------------------------------------------------------------------------------

void GameCollisionhandler::Initialize(mage::ecs::World& _world)
{
  auto& appMsgBus = _world.GetApplicationMessageBus();

  appMsgBus.Subscribe(this, &GameCollisionhandler::OnCollisionEvent);
}

// ------------------------------------------------------------------------------

void GameCollisionhandler::Tick(mage::ecs::World& _world, float _deltaTime)
{
  for (auto&& intersections : m_entityIntersections)
  {
    // Use movement controls for now to detect player
    auto* movementControlsA =
        _world.GetComponent<MovementControls>(intersections.first);

    auto* movementControlsB =
        _world.GetComponent<MovementControls>(intersections.second);

    if (movementControlsA)
    {
      // entityA is player

      auto* motionB =
          _world.GetComponent<mage::physics::Motion>(intersections.second);

      if (motionB)
      {
        // Entity collided with a moving object. Destroy entity and exit game.
        _world.DestroyEntity(intersections.first);

        auto& appMsgBus = _world.GetApplicationMessageBus();
        mage::core::OnExitAppEvent exitApp;
        appMsgBus.Broadcast(&exitApp);
      }
      else
      {
        // Collided with a static object. Bounce player
        auto* motionA =
            _world.GetComponent<mage::physics::Motion>(intersections.first);
        motionA->m_acceleration *= -1;
        motionA->m_velocity *= -1.1f;

        _world.AddComponent<mage::audio::PlaySoundEffect>(
            intersections.first, _world.GetSoundLibrary().GetAudioClip(
                                     "./res/audio/Blip_Select11.ogg"));
      }
    }
    else if (movementControlsB)
    {
      // entityB is player

      auto* motionA =
          _world.GetComponent<mage::physics::Motion>(intersections.first);

      if (motionA)
      {
        // Entity collided with a moving object. Destroy entity and exit game.
        _world.DestroyEntity(intersections.second);

        auto& appMsgBus = _world.GetApplicationMessageBus();
        mage::core::OnExitAppEvent exitApp;
        appMsgBus.Broadcast(&exitApp);
      }
      else
      {
        // Collided with a static object. Bounce player
        auto* motionB =
            _world.GetComponent<mage::physics::Motion>(intersections.second);
        motionB->m_acceleration *= -1;
        motionB->m_velocity *= -1.1f;

        _world.AddComponent<mage::audio::PlaySoundEffect>(
            intersections.second, _world.GetSoundLibrary().GetAudioClip(
                                      "./res/audio/Blip_Select11.ogg"));
      }
    }
    else
    {
      // neither is player

      auto* motionA =
          _world.GetComponent<mage::physics::Motion>(intersections.first);
      auto* motionB =
          _world.GetComponent<mage::physics::Motion>(intersections.second);

      // Destroy any entity that's moving and collided
      if (motionA)
      {
        _world.DestroyEntity(intersections.first);
      }
      if (motionB)
      {
        _world.DestroyEntity(intersections.second);
      }
    }
  }

  m_entityIntersections.clear();
}

// ------------------------------------------------------------------------------

void GameCollisionhandler::OnCollisionEvent(
    mage::physics::AABBIntersectionsEvent* _event)
{
  m_entityIntersections = _event->m_entityIntersections;
}

// ------------------------------------------------------------------------------
