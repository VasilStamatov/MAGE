#pragma once

#include "AudioDevice.h"

#include <unordered_map>

namespace mage
{
namespace audio
{

struct AudioSourceComponent
{
  AudioBufferHandle m_audioClip;
  AudioSourceHandle m_source;
};

// ------------------------------------------------------------------------------

struct OggData
{
  std::vector<char> m_audioBuffer;
  AudioFormat m_format;
  int m_frequency;
};

// ------------------------------------------------------------------------------

class SoundLibrary
{
public:
  SoundLibrary(AudioDevice& _audioDevice);

  void AddAudioClip(const std::string& _audioFile);
  AudioBufferHandle GetAudioClip(const std::string& _audioFile);

private:
  OggData LoadOgg(const std::string& _audioFile);

private:
  std::unordered_map<std::uint32_t, AudioBufferHandle> m_audioClips;

  AudioDevice& m_audioDevice;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage