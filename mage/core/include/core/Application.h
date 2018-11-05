#pragma once

#include "ecs/World.h"
#include "video/InputManager.h"
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

class Application
{
public:
  Application();
  virtual ~Application() {}

  // ------------------------------------------------------------------------------

  void Run();
  void Stop();

  // ------------------------------------------------------------------------------

  void TransitionToNextWorld();
  void TransitionToPreviousWorld();

  // ------------------------------------------------------------------------------

private:
  virtual void AddGameWorlds() = 0;

  // ------------------------------------------------------------------------------

  void InitializeSubSystems();
  void ShutdownSubSystems();

  // ------------------------------------------------------------------------------

  void Update(float _deltaTime);

  // ------------------------------------------------------------------------------

protected:
  std::vector<std::unique_ptr<ecs::World>> m_gameWorlds;

private:
  video::Video m_video;
  video::InputManager m_inputManager;

  std::int32_t m_currentWorldId;
  std::int32_t m_nextWorldId;
  ApplicationState m_state;
};

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage