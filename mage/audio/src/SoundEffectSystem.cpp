#include "audio/SoundEffectSystem.h"

#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"
#include "messaging/MessageBus.h"

#include <iostream>

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

SoundEffectSource::SoundEffectSource(AudioSourceHandle _audioSource, float _vol,
                                     float _var)
    : m_source(_audioSource)
    , m_volume(_vol)
    , m_variance(_var)
{
}

// ------------------------------------------------------------------------------

PlaySoundEffect::PlaySoundEffect(AudioBufferHandle _soundClip)
    : m_soundClip(std::move(_soundClip))
{
}

// ------------------------------------------------------------------------------

SoundEffectSystem::SoundEffectSystem(AudioDevice& _audioDevice)
    : m_audioDevice(_audioDevice)
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<SoundEffectSource>();
  m_systemSignature.AddComponent<PlaySoundEffect>();
}

// ------------------------------------------------------------------------------

void SoundEffectSystem::Tick(ecs::World& _world, float _deltaTime)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto& source = _world.GetComponent<SoundEffectSource>(entity);

    if (m_audioDevice.IsSourcePlaying(source.m_source))
    {
      // Can't play something while already playing
      continue;
    }

    auto& soundEffect = _world.GetComponent<PlaySoundEffect>(entity);
    auto& location =
        _world.GetComponent<ecs::common::TransformComponent>(entity)
            .m_transform.GetTranslation();

    // std::cout << "Playing Source From: " << location << std::endl;

    m_audioDevice.SetSourceSound(source.m_source, soundEffect.m_soundClip,
                                 source.m_volume, source.m_variance);

    m_audioDevice.PlaySource(source.m_source, location);

    // Remove after the effect has been played
    _world.RemoveComponent<PlaySoundEffect>(entity);
  }
}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage