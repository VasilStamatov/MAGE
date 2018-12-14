#pragma once

#include "AudioSystem.h"
#include "SoundLibrary.h"

namespace mage
{

namespace core
{
class World;
}

namespace audio
{

/////////////////////////////////////////////////
/// Audio world which contains all of audio related systems
/////////////////////////////////////////////////
class AudioWorld
{
public:
  AudioWorld(AudioDevice& _audioDevice, core::World& _ownerWorld);
  ~AudioWorld();

  // ------------------------------------------------------------------------------

  void Initialize();
  void Uninitialize();

  // ------------------------------------------------------------------------------

  void Tick();

  // ------------------------------------------------------------------------------

  void UpdateEntityStatus(ecs::Entity& _entity,
                          ecs::ComponentMask _entitySignature);

  // ------------------------------------------------------------------------------

  void AddAudioSystem(std::unique_ptr<AudioSystem> _system);

  inline SoundLibrary& GetSoundLibrary() { return m_soundLibrary; }

private:
  std::vector<std::unique_ptr<AudioSystem>> m_audioSystems;

  SoundLibrary m_soundLibrary;
  AudioDevice& m_audioDevice;
  core::World& m_ownerWorld;
};

} // namespace audio
} // namespace mage