#include "demo/GameWorld.h"

#include "demo/BlurPipeline.h"
#include "demo/CameraControlSystem.h"
#include "demo/MovementControlSystem.h"

#include <audio/SoundEffectSystem.h>
#include <audio/SoundListenerSystem.h>
#include <core/Application.h>
#include <ecs_common/CameraComponent.h>
#include <ecs_common/TransformComponent.h>
#include <graphics/SkyboxRenderer.h>
#include <graphics/StaticMeshRenderer.h>
#include <gui/Button.h>
#include <gui/ButtonEventHandler.h>
#include <gui/ButtonRenderer.h>
#include <physics/AABBCollisionSystem.h>
#include <physics/BasicCollisionResolution.h>
#include <physics/MotionSystem.h>

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
  AddGameSystem(std::make_unique<MovementControlSystem>());
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

  AddRenderingSystem(
      std::make_unique<mage::graphics::SkyboxRenderer>(mage::graphics::GLShader(
          "./res/shaders/Skybox.vert", "./res/shaders/Skybox.frag")));

  // AddPostProcessPass(std::make_unique<BlurPipeline>(
  //     mage::graphics::GLShader("./res/shaders/ScreenCoordPass.vert",
  //                              "./res/shaders/LightKeyPass.frag"),
  //     mage::graphics::GLShader("./res/shaders/ScreenCoordPass.vert",
  //                              "./res/shaders/Blur.frag"),
  //     mage::graphics::GLShader("./res/shaders/ScreenCoordPass.vert",
  //                              "./res/shaders/AdditiveMerge.frag"),
  //     8));

  AddPostProcessPass(std::make_unique<mage::graphics::CopyToTargetPipeline>());

  // GUI's are rendered last on top of the processed image
  AddGUISystem(std::make_unique<mage::gui::ButtonRenderer>(
      mage::graphics::GLShader("./res/shaders/WorldCoordQuad.vert",
                               "./res/shaders/DirectCopy.frag")));
}

void GameWorld::AddEntitiesAndComponents()
{
  const auto& viewport = m_screenCamera.GetViewport();
  std::int32_t windowWidth = viewport[2];
  std::int32_t windowHeight = viewport[1];

  // -------------- Load Resources ----------------------------

  m_soundLibrary.AddAudioClip("./res/audio/Blip_Select11.ogg");
  m_soundLibrary.AddAudioClip("./res/audio/neocrey - Last Cyber Dance.ogg");
  m_soundLibrary.AddAudioSource("CameraSource");
  mage::graphics::OBJModel cube("./res/models/cube.obj");
  mage::graphics::OBJModel plane("./res/models/plane.obj");

  // -------------- Load Resources ----------------------------

  // -------------- Make Skybox ----------------------------
  {
    auto skybox = CreateEntity();

    std::string skyboxPaths[] = {
        "./res/textures/sor_lake1/sor_lake1/lake1_rt.JPG",
        "./res/textures/sor_lake1/sor_lake1/lake1_lf.JPG",
        "./res/textures/sor_lake1/sor_lake1/lake1_up.JPG",
        "./res/textures/sor_lake1/sor_lake1/lake1_dn.JPG",
        "./res/textures/sor_lake1/sor_lake1/lake1_ft.JPG",
        "./res/textures/sor_lake1/sor_lake1/lake1_bk.JPG"};

    auto& skyboxComp =
        skybox.AddComponent<mage::graphics::SkyboxComponent>(skyboxPaths);
  }
  // -------------- Make Skybox ----------------------------

  // ----------------- Make player controlled entity ---------------------
  {
    auto renderedEntity = CreateEntity();

    auto& transform =
        renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

    transform.m_transform.SetTranslation(mage::math::Vec3f(0.0f, 0.0f, -5.0f));

    auto& staticMeshComp =
        renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
            cube, m_textureLibrary.Get("./res/textures/bricks.jpg"));

    auto& motionComponent =
        renderedEntity.AddComponent<mage::physics::Motion>();
    auto& colliderComponent =
        renderedEntity.AddComponent<mage::physics::AABBCollider>(
            cube.GetAABB());

    auto& movementController = renderedEntity.AddComponent<MovementControls>();
  }
  // ----------------- Make player controlled entity ---------------------

  // ----------------- Make Camera ----------------------------
  {
    auto camera = CreateEntity();

    auto& cameraComp = camera.AddComponent<mage::ecs::common::CameraComponent>(
        *this, mage::math::Vec4i32(0, 0, 1024, 576), 70.0f, 0.1f, 100.0f, true);

    auto& addedCamera = GetCamera(cameraComp.m_cameraId);

    addedCamera.MakeRenderToTarget();

    auto& transformComp =
        camera.AddComponent<mage::ecs::common::TransformComponent>()
            .m_transform;

    transformComp.Translate(mage::math::Vec3f(0.0f, 15.0f, 0.0f));

    transformComp.Rotate(
        mage::math::Quatf::GenRotationX(mage::math::ToRadians(45.0f)));

    addedCamera.SetView(
        transformComp.GetRotation().ToMat4() *
        mage::math::GenTranslationMat(transformComp.GetTranslation() * -1));

    // auto& cameraControlComponent =
    //     camera.AddComponent<CameraControlComponent>();

    camera.AddComponent<mage::audio::SoundEffectSource>(
        m_soundLibrary.GetAudioSource("CameraSource"), 0.02f, 1.0f);

    // Play this looping bgm
    camera.AddComponent<mage::audio::PlaySoundEffect>(
        m_soundLibrary.GetAudioClip(
            "./res/audio/neocrey - Last Cyber Dance.ogg"),
        true);

    camera.AddComponent<mage::audio::SoundListener>();
  }
  // ----------------- Make Camera ----------------------------

  // ----------------- Make other entities ---------------------
  {

    // -------- first Wall ---------

    auto renderedEntity = CreateEntity();

    auto& transform =
        renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

    transform.m_transform.SetTranslation(mage::math::Vec3f(15.0f, 0.0f, -5.0f));

    transform.m_transform.Rotate(
        mage::math::Quatf::GenRotationZ(mage::math::ToRadians(90.0f)));

    auto& staticMeshComp =
        renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
            plane, m_textureLibrary.Get("./res/textures/sand.jpg"));

    auto& colliderComponent =
        renderedEntity.AddComponent<mage::physics::AABBCollider>(
            plane.GetAABB());

    // -------- Second Wall ---------

    auto renderedEntity2 = CreateEntity();

    auto& transform2 =
        renderedEntity2.AddComponent<mage::ecs::common::TransformComponent>();

    transform2.m_transform.SetTranslation(
        mage::math::Vec3f(-15.0f, 0.0f, -5.0f));

    transform2.m_transform.Rotate(
        mage::math::Quatf::GenRotationZ(mage::math::ToRadians(-90.0f)));

    auto& staticMeshComp2 =
        renderedEntity2.AddComponent<mage::graphics::StaticMeshComponent>(
            plane, m_textureLibrary.Get("./res/textures/sand.jpg"));

    auto& colliderComponent2 =
        renderedEntity2.AddComponent<mage::physics::AABBCollider>(
            plane.GetAABB());

    // -------- Floor ---------

    // auto renderedEntity3 = CreateEntity();

    // auto& transform3 =
    //     renderedEntity3.AddComponent<mage::ecs::common::TransformComponent>();

    // transform3.m_transform.SetTranslation(mage::math::Vec3f(0.0, 0.0f,
    // -15.0f)); transform3.m_transform.SetScale(mage::math::Vec3f(70.0,
    // 1.0f, 70.0f));

    // // transform3.m_transform.Rotate(
    // //     mage::math::Quatf::GenRotationZ(mage::math::ToRadians(-90.0f)));

    // auto& staticMeshComp3 =
    //     renderedEntity3.AddComponent<mage::graphics::StaticMeshComponent>(
    //         plane,
    //         m_textureLibrary.Get("./res/textures/starfield.jpg"/*, true,
    //                              mage::graphics::TextureParameters(
    //                                  mage::graphics::TextureFormat::RGBA,
    //                                  mage::graphics::TextureFilter::Linear,
    //                                  mage::graphics::TextureWrap::Repeat)*/));
  }
  // ----------------- Make other entities ---------------------

  // -------------------- Add some GUI -------------------------
  {
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