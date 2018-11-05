#include "core/Application.h"

#include "core/Timer.h"

#include <iostream>

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

using namespace std::chrono_literals;

// ------------------------------------------------------------------------------

constexpr std::chrono::nanoseconds c_timestep(16ms);

// ------------------------------------------------------------------------------

Application::Application()
    : m_gameWorlds()
    , m_video()
    , m_currentWorldId(0)
    , m_nextWorldId(-1)
    , m_state(ApplicationState::Running)
{
}

// ------------------------------------------------------------------------------

void Application::Run(int argc, const char** argv)
{
  std::cout << "Argc: " << argc << " /--/ Argv: " << argv << std::endl;

  std::chrono::nanoseconds lag(0ns);

  InitializeSubSystems();

  AddGameWorlds();
  m_gameWorlds[m_currentWorldId]->OnEnter();

  Timer timer;

  while (m_state != ApplicationState::Exitting && !m_video.ShouldClose())
  {
    auto frameTime = timer.GetElapsedTime();

    if (frameTime > c_timestep / 100)
    {
      frameTime = c_timestep / 100;
    }

    timer.Renew();

    lag += frameTime;

    while (lag >= c_timestep)
    {
      lag -= c_timestep;

      m_inputManager.Update();
      Update(0.016f);
    }

    m_video.SwapBuffers();
  }

  ShutdownSubSystems();
}

// ------------------------------------------------------------------------------

void Application::Stop() { m_state = ApplicationState::Exitting; }

// ------------------------------------------------------------------------------

void Application::TransitionToNextWorld()
{
  m_nextWorldId = m_currentWorldId + 1;
  m_state = ApplicationState::Transitioning;
}

// ------------------------------------------------------------------------------

void Application::TransitionToPreviousWorld()
{
  m_nextWorldId = m_currentWorldId - 1;
  m_state = ApplicationState::Transitioning;
}

// ------------------------------------------------------------------------------

const video::InputManager& Application::GetInputManager() const
{
  return m_inputManager;
}

// ------------------------------------------------------------------------------

void Application::InitializeSubSystems()
{
  m_video.Initialize();
  m_inputManager.Initialize(m_video.GetWindow());
}

// ------------------------------------------------------------------------------

void Application::ShutdownSubSystems()
{
  m_inputManager.Shutdown();
  m_video.Shutdown();
}

// ------------------------------------------------------------------------------

void Application::Update(float _deltaTime)
{
  switch (m_state)
  {
    case ApplicationState::Running:
      m_gameWorlds[m_currentWorldId]->TickSystems(_deltaTime);
      break;

    case ApplicationState::Transitioning:
      assert(m_nextWorldId > -1);
      m_gameWorlds[m_currentWorldId]->OnExit();
      m_gameWorlds[m_nextWorldId]->OnEnter();
      m_currentWorldId = m_nextWorldId;
      m_nextWorldId = -1;
      m_state = ApplicationState::Running;
      break;

    default:
      break;
  }
}

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage