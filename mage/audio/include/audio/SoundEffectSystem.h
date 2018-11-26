#pragma once

#include "audio/AudioDevice.h"
#include "ecs/GameSystem.h"
#include "math/Vec.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The Sound Effect Source component contains the data for one audio source
/////////////////////////////////////////////////
struct SoundEffectSource : public ecs::Component
{
  SoundEffectSource(AudioSourceHandle _audioSource, float _vol, float _var);

  AudioSourceHandle m_source;
  float m_volume;
  float m_variance;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The Play Sound Effect component makes the sound system play a sound and then
/// removes it
/////////////////////////////////////////////////
struct PlaySoundEffect : public ecs::Component
{
  PlaySoundEffect(AudioBufferHandle _soundClip, bool _looping = false);

  AudioBufferHandle m_soundClip;
  bool m_looping;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The Sound Effect System plays a sound effect whenever a Play Sound Effect
/// component is added
/////////////////////////////////////////////////
class SoundEffectSystem : public ecs::GameSystem
{
public:
  SoundEffectSystem(AudioDevice& _audioDevice);

  virtual void Tick(ecs::World& _world, float _deltaTime) override;

private:
  AudioDevice& m_audioDevice;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage