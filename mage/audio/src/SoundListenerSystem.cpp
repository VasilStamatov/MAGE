#include "audio/SoundListenerSystem.h"

#include "core/World.h"
#include "ecs_common/TransformComponent.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

SoundListenerSystem::SoundListenerSystem(AudioDevice& _audioDevice)
    : AudioSystem(_audioDevice)
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<SoundListener>();
}

// ------------------------------------------------------------------------------

void SoundListenerSystem::Tick(core::World& _world)
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