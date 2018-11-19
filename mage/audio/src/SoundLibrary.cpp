#include "audio/SoundLibrary.h"

#include "exceptions/RuntimeError.h"

#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

SoundLibrary::SoundLibrary(AudioDevice& _audioDevice)
    : m_audioClips()
    , m_audioSources()
    , m_audioDevice(_audioDevice)
{
}

// ------------------------------------------------------------------------------

void SoundLibrary::AddAudioClip(const std::string& _audioFile)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_audioFile);

  assert(m_audioClips.count(hashedName) == 0);

  OggData audioData = LoadOgg(_audioFile);

  AudioBufferHandle handle = m_audioDevice.CreateAudioBuffer(
      audioData.m_format, audioData.m_audioBuffer.data(),
      audioData.m_audioBuffer.size(), audioData.m_frequency);

  m_audioClips[hashedName] = handle;
}

// ------------------------------------------------------------------------------

AudioBufferHandle SoundLibrary::GetAudioClip(const std::string& _audioFile)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_audioFile);

  assert(m_audioClips.count(hashedName) == 1);

  return m_audioClips[hashedName];
}

// ------------------------------------------------------------------------------

void SoundLibrary::AddAudioSource(const std::string& _unqiueSourceName)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_unqiueSourceName);

  assert(m_audioSources.count(hashedName) == 0);

  AudioSourceHandle handle = m_audioDevice.CreateAudioSource();
  m_audioSources[hashedName] = handle;
}

// ------------------------------------------------------------------------------

AudioSourceHandle
SoundLibrary::GetAudioSource(const std::string& _unqiueSourceName)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_unqiueSourceName);

  assert(m_audioSources.count(hashedName) == 1);

  return m_audioSources[hashedName];
}

// ------------------------------------------------------------------------------

OggData SoundLibrary::LoadOgg(const std::string& _audioFile)
{
  OggVorbis_File oggFile = {0};

  // Use the inbuilt fopen to create a file descriptor
  if (ov_fopen(_audioFile.c_str(), &oggFile) != 0)
  {
    throw RUNTIME_ERROR("Failed to open file [" + _audioFile +
                        "] for decoding");
  }

  OggData rtnData;

  vorbis_info* pInfo = ov_info(&oggFile, -1);

  if (pInfo->channels == 1)
  {
    rtnData.m_format = AudioFormat::Mono16;
  }
  else
  {
    rtnData.m_format = AudioFormat::Stereo16;
  }

  rtnData.m_frequency = pInfo->rate;

  int endian = 0;
  int bitStream = 0;
  long bytes = 0;
  char array[2048] = {0};

  while (true)
  {
    bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

    if (bytes < 0)
    {
      ov_clear(&oggFile);
      throw RUNTIME_ERROR("Failed to decode file [" + _audioFile + "]");
    }
    else if (bytes == 0)
    {
      break;
    }

    // Copy from temporary array into output buffer
    rtnData.m_audioBuffer.insert(rtnData.m_audioBuffer.end(), array,
                                 array + bytes);
  }

  ov_clear(&oggFile);

  return rtnData;
}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage