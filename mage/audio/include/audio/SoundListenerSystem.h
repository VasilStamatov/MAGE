#pragma once

#include "AudioDevice.h"
#include "AudioSystem.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// This empty component is just use for its ID to describe a sound listener
/// entity
/////////////////////////////////////////////////
struct SoundListener : public ecs::Component
{
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The sound listener system updates the listener location of the listener
/// entity
/////////////////////////////////////////////////
class SoundListenerSystem : public AudioSystem
{
public:
  SoundListenerSystem(AudioDevice& _audioDevice);

  virtual void Tick(core::World& _world) override;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage