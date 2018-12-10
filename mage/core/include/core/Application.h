#pragma once

#include "World.h"

#include "audio/AudioDevice.h"
#include "input/InputManager.h"
#include "messaging/MessageBus.h"
#include "renderer/RenderDevice.h"
#include "video/Video.h"

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The stata the application can be in
/////////////////////////////////////////////////
enum class ApplicationState : std::uint8_t
{
  Running,
  Transitioning,
  Exitting
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Event that can be fired to exit the application
/////////////////////////////////////////////////
struct OnExitAppEvent
{
};

/////////////////////////////////////////////////
/// Event that can be fired to transition to the next world
/////////////////////////////////////////////////
struct OnSetTransitionNextEvent
{
};

/////////////////////////////////////////////////
/// Event that can be fired to transition to the previous world
/////////////////////////////////////////////////
struct OnSetTransitionPreviousEvent
{
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Main Application class that must be inherited by the user-defined
/// application
/////////////////////////////////////////////////
class Application
{
public:
  Application();
  virtual ~Application() {}

  /////////////////////////////////////////////////
  /// Run starts the application and begins the game loop
  /////////////////////////////////////////////////
  void Run(int argc, const char** argv);

  inline audio::AudioDevice& GetAudioDevice() { return m_audioDevice; }
  inline graphics::RenderDevice& GetRenderDevice() { return m_renderDevice; }
  inline messaging::MessageBus& GetMessageBus()
  {
    return m_applicationMessageBus;
  }
  inline video::Video& GetVideo() { return m_video; }

private:
  void Stop();

  // ------------------------------------------------------------------------------

  void TransitionToNextWorld();
  void TransitionToPreviousWorld();

  // ------------------------------------------------------------------------------

  void InitializeSubSystems();
  void ShutdownSubSystems();

  // ------------------------------------------------------------------------------

  void Update(float _deltaSeconds);

  // ------------------------------------------------------------------------------

  void Render(float _interpolation);

  // ------------------------------------------------------------------------------

  void ExitAppEventHandler(OnExitAppEvent* _event);
  void SetTransitionNextEventHandler(OnSetTransitionNextEvent* _event);
  void SetTransitionPrevEventHandler(OnSetTransitionPreviousEvent* _event);

  // ------------------------------------------------------------------------------

  /////////////////////////////////////////////////
  /// AddGameWorlds is the virtual function inherited classes must implement
  /// which adds the user-defined game worlds
  /////////////////////////////////////////////////
  virtual void AddGameWorlds() = 0;

protected:
  messaging::MessageBus
      m_applicationMessageBus; ///< Application message bus for communication
  std::vector<std::unique_ptr<World>> m_gameWorlds; ///< all game worlds

private:
  video::Video m_video;               ///< Video class for window management
  input::InputManager m_inputManager; ///< Input class for input management
  audio::AudioDevice
      m_audioDevice; ///< audio device for the interface to the audio framework
  graphics::RenderDevice m_renderDevice; ///< render device for the interface to
                                         ///< the rendering framework

  std::int32_t m_currentWorldId;
  std::int32_t m_nextWorldId;
  ApplicationState m_state;
};

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage