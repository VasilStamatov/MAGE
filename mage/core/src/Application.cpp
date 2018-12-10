#include "core/Application.h"

#include "core/Timer.h"
#include "logger/LogDispatch.h"
#include "scheduler/Scheduler.h"

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
    , m_audioDevice()
    , m_renderDevice()
    , m_currentWorldId(0)
    , m_nextWorldId(-1)
    , m_state(ApplicationState::Running)
{
}

// ------------------------------------------------------------------------------

void Application::Run(int argc, const char** argv)
{
  m_applicationMessageBus.Subscribe(this, &Application::ExitAppEventHandler);
  m_applicationMessageBus.Subscribe(
      this, &Application::SetTransitionNextEventHandler);
  m_applicationMessageBus.Subscribe(
      this, &Application::SetTransitionPrevEventHandler);

#ifndef NDEBUG
  log::dispatch::RegisterLogger(std::make_unique<log::ConsoleLogger>(
      log::VerbosityFilterPolicy(log::LogType::Info), log::SimpleFormatPolicy(),
      log::ConsoleWriterPolicy()));
#endif

  InitializeSubSystems();

  AddGameWorlds();

  for (auto&& world : m_gameWorlds)
  {
    world->Initialize();
  }

  m_gameWorlds[m_currentWorldId]->OnEnter();
  m_gameWorlds[m_currentWorldId]->RefreshEntityState();

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
      Update(c_desiredFrameTimeMS / 1000.0f);
      m_gameWorlds[m_currentWorldId]->RefreshEntityState();
    }

    float interpolation =
        (timer.GetElapsedMilli() + c_desiredFrameTimeMS - millisElapsed) /
        c_desiredFrameTimeMS;

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
  scheduler::Initialize();
  m_video.Initialize();
  m_inputManager.Initialize();
  m_renderDevice.Initialize();
  m_audioDevice.Initialize();
}

// ------------------------------------------------------------------------------

void Application::ShutdownSubSystems()
{
  m_gameWorlds.clear();
  m_audioDevice.Shutdown();
  m_renderDevice.Shutdown();
  m_inputManager.Shutdown();
  m_video.Shutdown();
  scheduler::Shutdown();
}

// ------------------------------------------------------------------------------

void Application::Update(float _deltaSeconds)
{
  switch (m_state)
  {
    case ApplicationState::Running:
      m_gameWorlds[m_currentWorldId]->Update(_deltaSeconds);
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
  m_gameWorlds[m_currentWorldId]->Render(_interpolation);
}

// ------------------------------------------------------------------------------

void Application::ExitAppEventHandler(OnExitAppEvent* _event) { Stop(); }

// ------------------------------------------------------------------------------

void Application::SetTransitionNextEventHandler(
    OnSetTransitionNextEvent* _event)
{
  TransitionToNextWorld();
}

// ------------------------------------------------------------------------------

void Application::SetTransitionPrevEventHandler(
    OnSetTransitionPreviousEvent* _event)
{
  TransitionToPreviousWorld();
}

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage