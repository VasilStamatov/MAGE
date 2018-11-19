#pragma once

#include "math/Vec.h"

#include <memory>

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

struct AudioBufferHandle
{
  std::uint32_t m_index : 8;
  std::uint32_t m_generation : 24;
};

// ------------------------------------------------------------------------------

struct AudioSourceHandle
{
  std::uint32_t m_index : 8;
  std::uint32_t m_generation : 24;
};

// ------------------------------------------------------------------------------

enum class AudioFormat
{
  Mono8,
  Stereo8,
  Mono16,
  Stereo16
};

// ------------------------------------------------------------------------------

class AudioDevice
{
public:
  AudioDevice();
  ~AudioDevice();

  // ------------------------------------------------------------------------------

  void Initialize();
  void Shutdown();

  // ------------------------------------------------------------------------------

  AudioBufferHandle CreateAudioBuffer(AudioFormat _format, const void* _data,
                                      int _size, int _frequency);
  void DestroyAudioBuffer(AudioBufferHandle _handle);

  // ------------------------------------------------------------------------------

  AudioSourceHandle CreateAudioSource();
  void DestroyAudioSource(AudioSourceHandle _handle);

  // ------------------------------------------------------------------------------

  bool IsSourcePlaying(AudioSourceHandle _source) const;

  // ------------------------------------------------------------------------------

  void SetSourceSound(AudioSourceHandle _source, AudioBufferHandle _sound,
                      float _volume, float _variance);

  void PlaySource(AudioSourceHandle _source, const math::Vec3f& _sourcePos);

  // ------------------------------------------------------------------------------

  void SetListenerPosition(const math::Vec3f& _listenerPos);

private:
  class Impl;

  std::unique_ptr<Impl> m_impl;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage