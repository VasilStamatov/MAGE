#include "audio/AudioDevice.h"

#include "exceptions/RuntimeError.h"

#include <assert.h>
#include <cstdint>
#include <iostream>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

// ------------------------------------------------------------------------------

std::string ALErrorToString(ALenum _errorCode)
{
  switch (_errorCode)
  {
    case AL_INVALID_NAME:
      return "A bad name (ID) was passed to an OpenAL function";
      break;
    case AL_INVALID_ENUM:
      return "An invalid enum value was passed to an OpenAL function";
      break;
    case AL_INVALID_VALUE:
      return "An invalid value was passed to an OpenAL function";
      break;
    case AL_INVALID_OPERATION:
      return "The requested operation is not valid";
      break;
    case AL_OUT_OF_MEMORY:
      return "The requested operation resulted in OpenAL running out of memory";
      break;
  }
  return "Unknown error code";
}

std::uint32_t ALCheckError() { return alGetError(); }

bool ALLogCall(const char* _function, const char* _file, int _line)
{
  std::uint32_t error = ALCheckError();
  if (error != AL_NO_ERROR)
  {
    std::string errorString("[GL ERROR] : " + ALErrorToString(error) + '\n' +
                            "\t File: " + _file + '\n' +
                            "\t Function: " + _function + '\n' +
                            "\t Line: " + std::to_string(_line) + '\n');

    std::cout << errorString;
    return false;
  }
  return true;
}

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

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

class AudioDevice::Impl
{
public:
  void Initialize();

  void Shutdown();

private:
  ALCdevice* m_device;
  ALCcontext* m_context;
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

  std::cout << "----------------------------------\n Initialized "
               "OpenAL:\n\tOutput Device: "
            << outputDevice << "\n\tCapture Device: " << captureDevice
            << "\n\tExtensions Available: " << extensionsAvailable
            << "\n----------------------------------\n";
}

// ------------------------------------------------------------------------------

void AudioDevice::Impl::Shutdown()
{
  alcMakeContextCurrent(NULL);
  alcDestroyContext(m_context);
  alcCloseDevice(m_device);
}

} // namespace audio
} // namespace mage