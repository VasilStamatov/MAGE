#include "audio/AudioWorld.h"

#include "audio/AudioDevice.h"

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

AudioWorld::AudioWorld(AudioDevice& _audioDevice, core::World& _ownerWorld)
    : m_audioSystems()
    , m_soundLibrary(_audioDevice)
    , m_audioDevice(_audioDevice)
    , m_ownerWorld(_ownerWorld)

{
}

// ------------------------------------------------------------------------------

AudioWorld::~AudioWorld() {}

// ------------------------------------------------------------------------------

void AudioWorld::Initialize() {}

// ------------------------------------------------------------------------------

void AudioWorld::Uninitialize() {}

// ------------------------------------------------------------------------------

void AudioWorld::Tick()
{
  for (auto&& audioSystem : m_audioSystems)
  {
    audioSystem->Tick(m_ownerWorld);
  }
}

// ------------------------------------------------------------------------------

void AudioWorld::UpdateEntityStatus(ecs::Entity& _entity,
                                    ecs::ComponentMask _entitySignature)
{
  for (auto&& audioSystem : m_audioSystems)
  {
    audioSystem->OnEntityComponentMaskChange(_entity, _entitySignature);
  }
}

// ------------------------------------------------------------------------------

void AudioWorld::AddAudioSystem(std::unique_ptr<AudioSystem> _system)
{
  m_audioSystems.emplace_back(std::move(_system));
}

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage