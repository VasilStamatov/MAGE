#include "audio/SoundEffectSystem.h"

#include "core/World.h"
#include "ecs_common/TransformComponent.h"
#include "messaging/MessageBus.h"

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

PlaySoundEffect::PlaySoundEffect(AudioBufferHandle _soundClip, bool _looping)
    : m_soundClip(std::move(_soundClip))
    , m_looping(_looping)
{
}

// ------------------------------------------------------------------------------

SoundEffectSystem::SoundEffectSystem(AudioDevice& _audioDevice)
    : AudioSystem(_audioDevice)
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<SoundEffectSource>();
  m_systemSignature.AddComponent<PlaySoundEffect>();
}

// ------------------------------------------------------------------------------

void SoundEffectSystem::Tick(core::World& _world)
{
  for (auto&& entity : m_registeredEntities)
  {
    auto* source = _world.GetComponent<SoundEffectSource>(entity);

    if (m_audioDevice.IsSourcePlaying(source->m_source))
    {
      // Can't play something while already playing
      continue;
    }

    auto* soundEffect = _world.GetComponent<PlaySoundEffect>(entity);
    auto& location =
        _world.GetComponent<ecs::common::TransformComponent>(entity)
            ->m_transform.GetTranslation();

    m_audioDevice.SetSourceSound(source->m_source, soundEffect->m_soundClip,
                                 source->m_volume, source->m_variance,
                                 soundEffect->m_looping);

    m_audioDevice.PlaySource(source->m_source, location);

    // Remove after the effect has been played
    _world.RemoveComponent<PlaySoundEffect>(entity);
  }
}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage