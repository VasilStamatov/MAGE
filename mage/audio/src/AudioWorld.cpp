#include "audio/AudioWorld.h"

#include "audio/AudioDevice.h"
#include "scheduler/Scheduler.h"

namespace mage
{
namespace audio
{

struct AudioTickData
{
  AudioTickData(core::World& _world,
                std::vector<std::unique_ptr<AudioSystem>>& _systems)
      : m_world(_world)
      , m_systems(_systems)
  {
  }

  core::World& m_world;
  std::vector<std::unique_ptr<AudioSystem>>& m_systems;
};

static void AudioTickTask(scheduler::Task* _task, const void* _taskData)
{
  const AudioTickData* data = static_cast<const AudioTickData*>(_taskData);

  for (auto&& system : data->m_systems)
  {
    system->Tick(data->m_world);
  }
}

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
  AudioTickData data(m_ownerWorld, m_audioSystems);

  auto* task = scheduler::CreateTask(AudioTickTask, &data, sizeof(data));

  // Let the audio systems work on a separate thread completely, as they do not
  // modify components. This is currently safe due to the nature of the program.
  scheduler::Run(task);
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