#pragma once

#include "audio/AudioDevice.h"
#include "ecs/GameSystem.h"
#include "math/Vec.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

struct SoundListener : public ecs::Component
{
};

// ------------------------------------------------------------------------------

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