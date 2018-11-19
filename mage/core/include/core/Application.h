#pragma once

#include "audio/AudioDevice.h"
#include "ecs/World.h"
#include "input/InputManager.h"
#include "messaging/MessageBus.h"
#include "renderer/RenderDevice.h"
#include "video/Video.h"

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

enum class ApplicationState : std::uint8_t
{
  Running,
  Transitioning,
  Exitting
};

// ------------------------------------------------------------------------------

struct OnExitAppEvent
{
};

struct OnSetTransitionNextEvent
{
};

struct OnSetTransitionPreviousEvent
{
};

// ------------------------------------------------------------------------------

class Application
{
public:
  Application();
  virtual ~Application() {}

  void Run(int argc, const char** argv);

  audio::AudioDevice& GetAudioDevice() { return m_audioDevice; }
  messaging::MessageBus& GetMessageBus() { return m_applicationMessageBus; }

private:
  void Stop();

  // ------------------------------------------------------------------------------

  void TransitionToNextWorld();
  void TransitionToPreviousWorld();

  // ------------------------------------------------------------------------------

  void InitializeSubSystems();
  void ShutdownSubSystems();

  // ------------------------------------------------------------------------------

  void Update(float _deltaTime);

  // ------------------------------------------------------------------------------

  void Render(float _interpolation);

  // ------------------------------------------------------------------------------

  void ExitAppEventHandler(OnExitAppEvent* _event);
  void SetTransitionNextEventHandler(OnSetTransitionNextEvent* _event);
  void SetTransitionPrevEventHandler(OnSetTransitionPreviousEvent* _event);

  // ------------------------------------------------------------------------------

  virtual void AddGameWorlds() = 0;

protected:
  messaging::MessageBus m_applicationMessageBus;
  std::vector<std::unique_ptr<ecs::World>> m_gameWorlds;

private:
  video::Video m_video;
  input::InputManager m_inputManager;
  audio::AudioDevice m_audioDevice;
  graphics::RenderDevice m_renderDevice;

  std::int32_t m_currentWorldId;
  std::int32_t m_nextWorldId;
  ApplicationState m_state;
};

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage