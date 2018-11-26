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
class SoundListenerSystem : public ecs::GameSystem
{
public:
  SoundListenerSystem(AudioDevice& _audioDevice);

  virtual void Tick(ecs::World& _world, float _deltaTime) override;

private:
  AudioDevice& m_audioDevice;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage