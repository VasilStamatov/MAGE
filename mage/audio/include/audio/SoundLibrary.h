#pragma once

#include "AudioDevice.h"

#include <unordered_map>

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The data that is loaded from an .ogg file
/////////////////////////////////////////////////
struct OggData
{
  std::vector<char> m_audioBuffer;
  AudioFormat m_format;
  int m_frequency;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The sound library which holds the sound resources and controls their
/// lifetime
/////////////////////////////////////////////////
class SoundLibrary
{
public:
  SoundLibrary(AudioDevice& _audioDevice);

  void AddAudioClip(const std::string& _audioFile);
  AudioBufferHandle GetAudioClip(const std::string& _audioFile);

  void AddAudioSource(const std::string& _unqiueSourceName);
  AudioSourceHandle GetAudioSource(const std::string& _unqiueSourceName);

private:
  OggData LoadOgg(const std::string& _audioFile);

private:
  std::unordered_map<std::uint32_t, AudioBufferHandle>
      m_audioClips; ///< loaded sound data
  std::unordered_map<std::uint32_t, AudioSourceHandle>
      m_audioSources; ///< generated audio sources

  AudioDevice&
      m_audioDevice; ///< the audio device which is needed to make the calls
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage