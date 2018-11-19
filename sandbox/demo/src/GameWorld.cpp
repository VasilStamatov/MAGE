#include "demo/GameWorld.h"

#include "demo/CameraControlSystem.h"

#include <audio/SoundEffectSystem.h>
#include <audio/SoundListenerSystem.h>
#include <core/Application.h>
#include <ecs_common/CameraComponent.h>
#include <ecs_common/TransformComponent.h>
#include <graphics/StaticMeshRenderer.h>

GameWorld::GameWorld(mage::core::Application& _application)
    : mage::ecs::World(_application)
    , m_audioDevice(_application.GetAudioDevice())
{
}

void GameWorld::AddSystems()
{
  AddGameSystem(std::make_unique<CameraControlSystem>());
  AddGameSystem(
      std::make_unique<mage::audio::SoundListenerSystem>(m_audioDevice));
  AddGameSystem(
      std::make_unique<mage::audio::SoundEffectSystem>(m_audioDevice));

  AddRenderingSystem(std::make_unique<mage::graphics::StaticMeshRenderer>(
      mage::graphics::GLShader("./res/shaders/StaticMesh.vert",
                               "./res/shaders/StaticMesh.frag")));
}

void GameWorld::AddEntitiesAndComponents()
{
  m_soundLibrary.AddAudioClip("./res/audio/Blip_Select11.ogg");
  m_soundLibrary.AddAudioSource("CameraSource");

  auto camera = CreateEntity();
  auto& cameraComp = camera.AddComponent<mage::ecs::common::CameraComponent>(
      *this, mage::math::GenPerspectiveMat(mage::math::ToRadians(70.0f),
                                           16.0f / 9.0f, 0.1f, 100.0f));
  auto& transformComp =
      camera.AddComponent<mage::ecs::common::TransformComponent>();

  auto& cameraControlComponent = camera.AddComponent<CameraControlComponent>();

  camera.AddComponent<mage::audio::SoundEffectSource>(
      m_soundLibrary.GetAudioSource("CameraSource"), 0.02f, 1.0f);

  camera.AddComponent<mage::audio::SoundListener>();

  auto renderedEntity = CreateEntity();
  auto& transform =
      renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

  transform.m_transform.SetTranslation(mage::math::Vec3f(0.0f, 0.0f, -5.0f));

  auto& staticMeshComp =
      renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
          "./res/models/cube.obj", "./res/textures/test.png");
}