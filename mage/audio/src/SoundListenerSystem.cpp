#include "audio/SoundListenerSystem.h"

#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

SoundListenerSystem::SoundListenerSystem(AudioDevice& _audioDevice)
    : m_audioDevice(_audioDevice)
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<SoundListener>();
}

// ------------------------------------------------------------------------------

void SoundListenerSystem::Tick(ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& location =
        _world.GetComponent<ecs::common::TransformComponent>(entity)
            ->m_transform.GetTranslation();

    m_audioDevice.SetListenerPosition(location);
  }
}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage