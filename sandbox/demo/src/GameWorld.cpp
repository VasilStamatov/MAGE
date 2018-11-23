#include "demo/GameWorld.h"

#include "demo/CameraControlSystem.h"

#include <audio/SoundEffectSystem.h>
#include <audio/SoundListenerSystem.h>
#include <core/Application.h>
#include <ecs_common/CameraComponent.h>
#include <ecs_common/TransformComponent.h>
#include <graphics/StaticMeshRenderer.h>
#include <physics/AABBCollisionSystem.h>
#include <physics/BasicCollisionResolution.h>
#include <physics/MotionSystem.h>
#include <physics/MovementControlSystem.h>

GameWorld::GameWorld(mage::core::Application& _application)
    : mage::ecs::World(_application)
    , m_audioDevice(_application.GetAudioDevice())
{
}

void GameWorld::AddSystems()
{
  // Add systems in desired order to be executed

  AddGameSystem(std::make_unique<CameraControlSystem>());
  AddGameSystem(std::make_unique<mage::physics::MovementControlSystem>());
  AddGameSystem(std::make_unique<mage::physics::AABBCollisionSystem>());
  AddGameSystem(std::make_unique<mage::physics::BasicCollisionResolution>());
  AddGameSystem(std::make_unique<mage::physics::MotionSystem>());
  AddGameSystem(
      std::make_unique<mage::audio::SoundListenerSystem>(m_audioDevice));
  AddGameSystem(
      std::make_unique<mage::audio::SoundEffectSystem>(m_audioDevice));

  AddRenderingSystem(std::make_unique<mage::graphics::StaticMeshRenderer>(
      mage::graphics::GLShader("./res/shaders/StaticMesh.vert",
                               "./res/shaders/StaticMesh.frag")));

  AddPostProcessPass(std::make_unique<mage::graphics::NullPostProcessPass>());
}

void GameWorld::AddEntitiesAndComponents()
{
  // -------------- Load Resources ----------------------------

  m_soundLibrary.AddAudioClip("./res/audio/Blip_Select11.ogg");
  m_soundLibrary.AddAudioSource("CameraSource");
  mage::graphics::OBJModel cube("./res/models/cube.obj");

  // -------------- Load Resources ----------------------------

  // ----------------- Make Camera ----------------------------
  {
    auto camera = CreateEntity();

    auto& cameraComp = camera.AddComponent<mage::ecs::common::CameraComponent>(
        *this, mage::math::Vec4i32(0, 0, 1024, 576), 70.0f, 0.1f, 100.0f, true);

    GetCamera(cameraComp.m_cameraId).MakeRenderToTarget(1024, 1024);

    auto& transformComp =
        camera.AddComponent<mage::ecs::common::TransformComponent>();

    auto& cameraControlComponent =
        camera.AddComponent<CameraControlComponent>();

    camera.AddComponent<mage::audio::SoundEffectSource>(
        m_soundLibrary.GetAudioSource("CameraSource"), 0.02f, 1.0f);

    camera.AddComponent<mage::audio::SoundListener>();
  }
  // ----------------- Make Camera ----------------------------

  // ----------------- Make player controlled entity ---------------------
  {
    auto renderedEntity = CreateEntity();

    auto& transform =
        renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

    transform.m_transform.SetTranslation(mage::math::Vec3f(0.0f, 0.0f, -5.0f));

    auto& staticMeshComp =
        renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
            cube, "./res/textures/test.png");

    auto& motionComponent =
        renderedEntity.AddComponent<mage::physics::Motion>();
    auto& colliderComponent =
        renderedEntity.AddComponent<mage::physics::AABBCollider>(
            cube.GetAABB());

    auto& movementController =
        renderedEntity.AddComponent<mage::physics::MovementControls>();
  }
  // ----------------- Make player controlled entity ---------------------

  // ----------------- Make other entities ---------------------
  {
    for (size_t i = 0; i < 2; i++)
    {
      auto renderedEntity = CreateEntity();

      auto& transform =
          renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

      transform.m_transform.SetTranslation(
          mage::math::Vec3f(5.0f + i * 5.0f, 0.0f, -5.0f));

      auto& staticMeshComp =
          renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
              cube, "./res/textures/test.png");

      auto& motionComponent =
          renderedEntity.AddComponent<mage::physics::Motion>();
      auto& colliderComponent =
          renderedEntity.AddComponent<mage::physics::AABBCollider>(
              cube.GetAABB());
    }
  }
  // ----------------- Make other entities ---------------------
}