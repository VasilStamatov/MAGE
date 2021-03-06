#include "audio/AudioDevice.h"

#include "exceptions/RuntimeError.h"
#include "logger/LogDispatch.h"

#include <array>
#include <assert.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>

// ------------------------------------------------------------------------------

namespace mage
{
namespace audio
{

namespace
{

// ------------------------------------------------------------------------------

std::string ALErrorToString(ALenum _errorCode)
{
  switch (_errorCode)
  {
    case AL_INVALID_NAME:
      return "A bad name (ID) was passed to an OpenAL function";
    case AL_INVALID_ENUM:
      return "An invalid enum value was passed to an OpenAL function";
    case AL_INVALID_VALUE:
      return "An invalid value was passed to an OpenAL function";
    case AL_INVALID_OPERATION:
      return "The requested operation is not valid";
    case AL_OUT_OF_MEMORY:
      return "The requested operation resulted in OpenAL running out of memory";
  }
  return "Unknown error code";
}

// ------------------------------------------------------------------------------

std::uint32_t ALCheckError() { return alGetError(); }

// ------------------------------------------------------------------------------

bool ALLogCall(const char* _function, const char* _file, int _line)
{
  std::uint32_t error = ALCheckError();
  if (error != AL_NO_ERROR)
  {
    LOG_FATAL("AudioDevice", "[AL ERROR] : " + ALErrorToString(error) + '\n' +
                                 "\t File: " + _file + '\n' +
                                 "\t Function: " + _function + '\n' +
                                 "\t Line: " + std::to_string(_line) + '\n');

    return false;
  }
  return true;
}

// ------------------------------------------------------------------------------

ALenum GetALFormat(AudioFormat _format)
{
  switch (_format)
  {
    case AudioFormat::Mono8:
      return AL_FORMAT_MONO8;
    case AudioFormat::Stereo8:
      return AL_FORMAT_STEREO8;

    case AudioFormat::Mono16:
      return AL_FORMAT_MONO16;
    case AudioFormat::Stereo16:
      return AL_FORMAT_STEREO16;
  }

  return 0;
}

} // namespace

// ------------------------------------------------------------------------------

#ifdef NDEBUG
#define ALCall(expr) expr
#else
#define ALCall(expr)                                                           \
  ALCheckError();                                                              \
  expr;                                                                        \
  assert(ALLogCall(#expr, __FILE__, __LINE__))
#endif

// ------------------------------------------------------------------------------

static constexpr std::uint32_t c_maxAudioBuffersAllocated = 1 << 8;

// ------------------------------------------------------------------------------

class AudioDevice::Impl
{
public:
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
                      float _volume, float _variance, bool _looping);

  void PlaySource(AudioSourceHandle _source, const math::Vec3f& _sourcePos);

  void StopPlayingSource(AudioSourceHandle _source);

  // ------------------------------------------------------------------------------

  void SetListenerPosition(const math::Vec3f& _listenerPos);

private:
  ALCdevice* m_device;
  ALCcontext* m_context;

  ALuint m_audioDataBuffers[c_maxAudioBuffersAllocated];
  ALuint m_audioSourceBuffers[c_maxAudioBuffersAllocated];

  std::vector<std::uint32_t> m_audioBufferGenerations;
  std::vector<std::uint32_t> m_freeAudioBufferIds;

  std::vector<std::uint32_t> m_audioSourcesGenerations;
  std::vector<std::uint32_t> m_freeAudioSourcesIds;
};

// ------------------------------------------------------------------------------

AudioDevice::AudioDevice()
    : m_impl(std::make_unique<AudioDevice::Impl>())
{
}

// ------------------------------------------------------------------------------

AudioDevice::~AudioDevice() {}

// ------------------------------------------------------------------------------

void AudioDevice::Initialize() { m_impl->Initialize(); }

// ------------------------------------------------------------------------------

void AudioDevice::Shutdown() { m_impl->Shutdown(); }

// ------------------------------------------------------------------------------

AudioBufferHandle AudioDevice::CreateAudioBuffer(AudioFormat _format,
                                                 const void* _data, int _size,
                                                 int _frequency)
{
  return m_impl->CreateAudioBuffer(_format, _data, _size, _frequency);
}

// ------------------------------------------------------------------------------

void AudioDevice::DestroyAudioBuffer(AudioBufferHandle _handle)
{
  m_impl->DestroyAudioBuffer(_handle);
}

// ------------------------------------------------------------------------------

AudioSourceHandle AudioDevice::CreateAudioSource()
{
  return m_impl->CreateAudioSource();
}

// ------------------------------------------------------------------------------

void AudioDevice::DestroyAudioSource(AudioSourceHandle _handle)
{
  m_impl->DestroyAudioSource(_handle);
}

// ------------------------------------------------------------------------------

bool AudioDevice::IsSourcePlaying(AudioSourceHandle _source) const
{
  return m_impl->IsSourcePlaying(_source);
}

// ------------------------------------------------------------------------------

void AudioDevice::SetSourceSound(AudioSourceHandle _source,
                                 AudioBufferHandle _sound, float _volume,
                                 float _variance, bool _looping)
{
  m_impl->SetSourceSound(_source, _sound, _volume, _variance, _looping);
}

// ------------------------------------------------------------------------------

void AudioDevice::PlaySource(AudioSourceHandle _source,
                             const math::Vec3f& _sourcePos)
{
  m_impl->PlaySource(_source, _sourcePos);
}

// ------------------------------------------------------------------------------

void AudioDevice::SetListenerPosition(const math::Vec3f& _listenerPos)
{
  m_impl->SetListenerPosition(_listenerPos);
}

// ------------------------------------------------------------------------------

void AudioDevice::StopPlayingSource(AudioSourceHandle _source)
{
  m_impl->StopPlayingSource(_source);
}

// ------------------------------------------------------------------------------
//                                IMPLEMENTATION
// ------------------------------------------------------------------------------

void AudioDevice::Impl::Initialize()
{
  m_device = alcOpenDevice(NULL);
  if (!m_device)
  {
    throw RUNTIME_ERROR("Failed to open ALC Device");
  }

  m_context = alcCreateContext(m_device, NULL);

  if (!m_context)
  {
    throw RUNTIME_ERROR("Failed to create ALC Context");
  }

  if (!alcMakeContextCurrent(m_context))
  {
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
    throw RUNTIME_ERROR("Could not set the context to current");
  }

  ALCall(auto outputDevice = alcGetString(m_device, ALC_DEVICE_SPECIFIER));
  ALCall(auto captureDevice =
             alcGetString(m_device, ALC_CAPTURE_DEVICE_SPECIFIER));
  ALCall(auto extensionsAvailable = alcGetString(m_device, ALC_EXTENSIONS));

  LOG_INFO("AudioDevice",
           "----------------------------------\n Initialized "
           "OpenAL:\n\tOutput Device: " +
               std::string(outputDevice) +
               "\n\tCapture Device: " + captureDevice +
               "\n\tExtensions Available: " + extensionsAvailable +
               "\n----------------------------------\n");

  ALCall(alGenBuffers(c_maxAudioBuffersAllocated, m_audioDataBuffers));
  ALCall(alGenSources(c_maxAudioBuffersAllocated, m_audioSourceBuffers));
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::Shutdown()
{
  ALCall(alDeleteSources(c_maxAudioBuffersAllocated, m_audioSourceBuffers));
  ALCall(alDeleteBuffers(c_maxAudioBuffersAllocated, m_audioDataBuffers));
  alcMakeContextCurrent(NULL);
  alcDestroyContext(m_context);
  alcCloseDevice(m_device);
}

// ------------------------------------------------------------------------------

AudioBufferHandle AudioDevice::Impl::CreateAudioBuffer(AudioFormat _format,
                                                       const void* _data,
                                                       int _size,
                                                       int _frequency)
{
  std::uint32_t audioBufferId = 0;

  if (!m_freeAudioBufferIds.empty())
  {
    audioBufferId = m_freeAudioBufferIds.back();
    m_freeAudioBufferIds.pop_back();
  }
  else
  {
    m_audioBufferGenerations.emplace_back(0);
    audioBufferId = m_audioBufferGenerations.size() - 1;
    assert(audioBufferId < c_maxAudioBuffersAllocated);
  }

  ALCall(alBufferData(m_audioDataBuffers[audioBufferId], GetALFormat(_format),
                      _data, _size, _frequency));

  return AudioBufferHandle{audioBufferId,
                           m_audioBufferGenerations[audioBufferId]};
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::DestroyAudioBuffer(AudioBufferHandle _handle)
{
  assert(_handle.m_generation == m_audioBufferGenerations[_handle.m_index]);

  std::uint32_t index = _handle.m_index;
  ++m_audioBufferGenerations[index];
  m_freeAudioBufferIds.emplace_back(index);
}

// ------------------------------------------------------------------------------

AudioSourceHandle AudioDevice::Impl::CreateAudioSource()
{
  std::uint32_t audioSourceId = 0;

  if (!m_freeAudioSourcesIds.empty())
  {
    audioSourceId = m_freeAudioSourcesIds.back();
    m_freeAudioSourcesIds.pop_back();
  }
  else
  {
    m_audioSourcesGenerations.emplace_back(0);
    audioSourceId = m_audioSourcesGenerations.size() - 1;
    assert(audioSourceId < c_maxAudioBuffersAllocated);
  }

  return AudioSourceHandle{audioSourceId,
                           m_audioSourcesGenerations[audioSourceId]};
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::DestroyAudioSource(AudioSourceHandle _handle)
{
  assert(_handle.m_generation == m_audioSourcesGenerations[_handle.m_index]);

  std::uint32_t index = _handle.m_index;
  ++m_audioSourcesGenerations[index];
  m_freeAudioSourcesIds.emplace_back(index);
}

// ------------------------------------------------------------------------------

bool AudioDevice::Impl::IsSourcePlaying(AudioSourceHandle _source) const
{
  ALint sourceState = 0;
  ALCall(alGetSourcei(m_audioSourceBuffers[_source.m_index], AL_SOURCE_STATE,
                      &sourceState));

  return sourceState == AL_PLAYING;
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::SetSourceSound(AudioSourceHandle _source,
                                       AudioBufferHandle _sound, float _volume,
                                       float _variance, bool _looping)
{
  assert(_source.m_generation == m_audioSourcesGenerations[_source.m_index]);
  assert(_sound.m_generation == m_audioBufferGenerations[_sound.m_index]);

  ALCall(alSourcef(m_audioSourceBuffers[_source.m_index], AL_PITCH, _variance));
  ALCall(alSourcef(m_audioSourceBuffers[_source.m_index], AL_GAIN, _volume));
  ALCall(
      alSourcef(m_audioSourceBuffers[_source.m_index], AL_LOOPING, _looping));

  ALCall(alSourcei(m_audioSourceBuffers[_source.m_index], AL_BUFFER,
                   m_audioDataBuffers[_sound.m_index]));
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::PlaySource(AudioSourceHandle _source,
                                   const math::Vec3f& _sourcePos)
{
  assert(_source.m_generation == m_audioSourcesGenerations[_source.m_index]);

  ALCall(alSource3f(m_audioSourceBuffers[_source.m_index], AL_POSITION,
                    _sourcePos[0], _sourcePos[1], _sourcePos[2]));

  ALCall(alSourcePlay(m_audioSourceBuffers[_source.m_index]));
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::StopPlayingSource(AudioSourceHandle _source)
{
  assert(_source.m_generation == m_audioSourcesGenerations[_source.m_index]);

  ALCall(alSourceStop(m_audioSourceBuffers[_source.m_index]));
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::SetListenerPosition(const math::Vec3f& _listenerPos)
{
  ALCall(alListener3f(AL_POSITION, _listenerPos[0], _listenerPos[2],
                      _listenerPos[2]));
}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage