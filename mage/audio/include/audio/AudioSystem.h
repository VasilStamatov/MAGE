#pragma once

#include "ecs/System.h"

namespace mage
{
namespace audio
{

class AudioDevice;

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Base class for all audio systems
/////////////////////////////////////////////////
class AudioSystem : public ecs::System
{
public:
  AudioSystem(AudioDevice& _audioDevice);
  virtual ~AudioSystem();

  // ------------------------------------------------------------------------------

  virtual void Tick(core::World& _world) = 0;

protected:
  AudioDevice& m_audioDevice;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage