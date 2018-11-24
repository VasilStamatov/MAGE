#include "demo/GameWorld.h"

#include "demo/CameraControlSystem.h"

#include <audio/SoundEffectSystem.h>
#include <audio/SoundListenerSystem.h>
#include <core/Application.h>
#include <ecs_common/CameraComponent.h>
#include <ecs_common/TransformComponent.h>
#include <graphics/BlurPipeline.h>
#include <graphics/StaticMeshRenderer.h>
#include <gui/Button.h>
#include <gui/ButtonEventHandler.h>
#include <gui/ButtonRenderer.h>
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

  // AddGameSystem(std::make_unique<CameraControlSystem>());
  AddGameSystem(std::make_unique<mage::gui::ButtonEventHandler>());
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

  AddGUISystem(std::make_unique<mage::gui::ButtonRenderer>(
      mage::graphics::GLShader("./res/shaders/WorldCoordQuad.vert",
                               "./res/shaders/DirectCopy.frag")));

  // AddPostProcessPass(std::make_unique<mage::graphics::BlurPipeline>(
  //     mage::graphics::GLShader("./res/shaders/ScreenCoordPass.vert",
  //                              "./res/shaders/LightKeyPass.frag"),
  //     mage::graphics::GLShader("./res/shaders/ScreenCoordPass.vert",
  //                              "./res/shaders/Blur.frag"),
  //     mage::graphics::GLShader("./res/shaders/ScreenCoordPass.vert",
  //                              "./res/shaders/AdditiveMerge.frag"),
  //     8));

  AddPostProcessPass(std::make_unique<mage::graphics::CopyToTargetPipeline>());
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

    GetCamera(cameraComp.m_cameraId).MakeRenderToTarget();

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

  // -------------------- Add some GUI -------------------------
  {
    const auto& viewport = m_screenCamera.GetViewport();
    std::int32_t windowWidth = viewport[2];
    std::int32_t windowHeight = viewport[1];

    for (size_t i = 0; i < 2; i++)
    {
      auto button = CreateEntity();

      auto& buttonComp = button.AddComponent<mage::gui::Button>(
          mage::math::Vec2i32(i * 50, i * 50), mage::math::Vec2i32(50, 50));

      auto& guiTextureComp = button.AddComponent<mage::gui::GUITexture>(
          m_textureLibrary.Get("./res/textures/exit.png", false));

      auto& msgBus = GetApplicationMessageBus();

      auto& guiCallback =
          button.AddComponent<mage::gui::GUICallback>([&msgBus]() {
            mage::core::OnExitAppEvent exitApp;
            msgBus.Broadcast(&exitApp);
          });
    }
  }
  // -------------------- Add some GUI -------------------------
}