#include "core/Application.h"

#include "core/Timer.h"

#include <iostream>

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

constexpr std::int32_t c_desiredFPS = 25;
constexpr std::int32_t c_millisPerSecond = 1000;
constexpr std::int32_t c_desiredFrameTimeMS = c_millisPerSecond / c_desiredFPS;
constexpr std::int32_t c_maxUpdatesPerFrame = 5;

// ------------------------------------------------------------------------------

Application::Application()
    : m_applicationMessageBus()
    , m_gameWorlds()
    , m_video(m_applicationMessageBus)
    , m_inputManager(m_applicationMessageBus)
    , m_renderDevice()
    , m_currentWorldId(0)
    , m_nextWorldId(-1)
    , m_state(ApplicationState::Running)
{
}

// ------------------------------------------------------------------------------

void Application::Run(int argc, const char** argv)
{
  std::cout << "Argc: " << argc << " /--/ Argv: " << argv << std::endl;

  m_applicationMessageBus.Subscribe(this, &Application::ExitAppEventHandler);
  m_applicationMessageBus.Subscribe(
      this, &Application::SetTransitionNextEventHandler);
  m_applicationMessageBus.Subscribe(
      this, &Application::SetTransitionPrevEventHandler);

  InitializeSubSystems();

  AddGameWorlds();

  for (auto&& world : m_gameWorlds)
  {
    world->Initialize();
  }

  m_gameWorlds[m_currentWorldId]->OnEnter();

  Timer timer;
  float millisElapsed = timer.GetElapsedMilli();

  while (m_state != ApplicationState::Exitting && !m_video.ShouldClose())
  {
    std::int32_t numUpdates = 0;

    while (timer.GetElapsedMilli() > millisElapsed &&
           numUpdates < c_maxUpdatesPerFrame)
    {
      millisElapsed += c_desiredFrameTimeMS;
      numUpdates++;

      m_inputManager.Update();
      Update(1.0f);
    }

    float interpolation =
        (timer.GetElapsedMilli() + c_desiredFrameTimeMS - millisElapsed) /
        c_desiredFrameTimeMS;

    m_gameWorlds[m_currentWorldId]->TickRenderingSystems(interpolation);

    Render(interpolation);

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

void Application::InitializeSubSystems()
{
  m_video.Initialize();
  m_inputManager.Initialize();
  m_renderDevice.Initialize();
}

// ------------------------------------------------------------------------------

void Application::ShutdownSubSystems()
{
  m_gameWorlds.clear();
  m_renderDevice.Shutdown();
  m_inputManager.Shutdown();
  m_video.Shutdown();
}

// ------------------------------------------------------------------------------

void Application::Update(float _deltaTime)
{
  switch (m_state)
  {
    case ApplicationState::Running:
      m_gameWorlds[m_currentWorldId]->TickGameSystems(_deltaTime);
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

void Application::Render(float _interpolation)
{
  m_renderDevice.ClearBuffer(graphics::RendererBufferType::Color_Depth);
  m_renderDevice.SetViewport(0, 0, 1024, 576);
  m_gameWorlds[m_currentWorldId]->TickRenderingSystems(_interpolation);
}

// ------------------------------------------------------------------------------

void Application::ExitAppEventHandler(OnExitAppEvent* _event) { Stop(); }

// ------------------------------------------------------------------------------

void Application::SetTransitionNextEventHandler(
    OnSetTransitionNextEvent* _event)
{
  TransitionToNextWorld();
}

void Application::SetTransitionPrevEventHandler(
    OnSetTransitionPreviousEvent* _event)
{
  TransitionToPreviousWorld();
}

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage