#include "audio/AudioSystem.h"

#include "audio/AudioDevice.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

AudioSystem::AudioSystem(AudioDevice& _audioDevice)
    : m_audioDevice(_audioDevice)
{
}

// ------------------------------------------------------------------------------

AudioSystem::~AudioSystem() {}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage