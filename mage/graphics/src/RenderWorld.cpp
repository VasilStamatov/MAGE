#include "graphics/RenderWorld.h"

#include "core/Application.h"
#include "core/World.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

RenderWorld::RenderWorld(RenderDevice& _renderDevice, core::World& _ownerWorld)
    : m_renderingSystems()
    , m_postProcesses()
    , m_guiSystems()
    , m_gameCameras()
    // Declare the screen cam viewport as 0,heigth as origin
    // to match the screen coordinates This is needed so that
    // the rendered gui matches the gui location for event
    // handling. (needed for an ortho matrix which matches
    // screen origin)
    , m_screenCamera(math::Vec4i32(0.0f,
                                   _ownerWorld.GetApplication()
                                       .GetVideo()
                                       .GetWindowFramebufferSize()
                                       .second,
                                   _ownerWorld.GetApplication()
                                       .GetVideo()
                                       .GetWindowFramebufferSize()
                                       .first,
                                   0.0f),
                     -1.0f, 1.0f, _ownerWorld.GetApplication().GetMessageBus())
    , m_copyToTargetPass()
    , m_textureLibrary()
    , m_objModelLibrary()
    , m_renderDevice(_renderDevice)
    , m_ownerWorld(_ownerWorld)
{
}

// ------------------------------------------------------------------------------

RenderWorld::~RenderWorld() {}

// ------------------------------------------------------------------------------

void RenderWorld::Initialize() {}

// ------------------------------------------------------------------------------

void RenderWorld::Uninitialize() {}

// ------------------------------------------------------------------------------

void RenderWorld::Render(float _interpolation)
{
  RenderScene(_interpolation);
  ApplyPostProcesses();
  RenderGUI(_interpolation);
}

// ------------------------------------------------------------------------------

void RenderWorld::UpdateEntityStatus(ecs::Entity& _entity,
                                     ecs::ComponentMask _entitySignature)
{
  for (auto&& renderSystem : m_renderingSystems)
  {
    renderSystem->OnEntityComponentMaskChange(_entity, _entitySignature);
  }
  for (auto&& guiSystem : m_guiSystems)
  {
    guiSystem->OnEntityComponentMaskChange(_entity, _entitySignature);
  }
}

// ------------------------------------------------------------------------------

void RenderWorld::AddRenderingSystem(std::unique_ptr<RenderingSystem> _system)
{
  m_renderingSystems.emplace_back(std::move(_system));
}

// ------------------------------------------------------------------------------

void RenderWorld::AddPostProcessPipeline(
    std::unique_ptr<PostProcessPipeline> _pipeline)
{
  m_postProcesses.emplace_back(std::move(_pipeline));
}

// ------------------------------------------------------------------------------

void RenderWorld::AddGUISystem(std::unique_ptr<RenderingSystem> _system)
{
  m_guiSystems.emplace_back(std::move(_system));
}

/////////////////////////////////////////////////
/// Adds a perspective camera to the world. This doesn't need to be explicitly
/// called as it's done whenver a camera component is added. This is only
/// needed if a camera component is not required.
/////////////////////////////////////////////////
std::uint32_t RenderWorld::AddPerspectiveCamera(const math::Vec4i32& _viewport,
                                                float _fovDegrees, float _near,
                                                float _far,
                                                bool _listenForWindowResize)
{
  if (_listenForWindowResize)
  {
    m_gameCameras.emplace_back(_viewport, _fovDegrees, _near, _far,
                               m_ownerWorld.GetApplication().GetMessageBus());
  }
  else
  {
    m_gameCameras.emplace_back(_viewport, _fovDegrees, _near, _far);
  }
  return m_gameCameras.size() - 1;
}

/////////////////////////////////////////////////
/// Adds an orthographic camera to the world. This doesn't need to be
/// explicitly called as it's done whenver a camera component is added. This
/// is only needed if a camera component is not required.
/////////////////////////////////////////////////
std::uint32_t RenderWorld::AddOrthographicCamera(const math::Vec4i32& _viewport,
                                                 float _near, float _far,
                                                 bool _listenForWindowResize)
{
  if (_listenForWindowResize)
  {
    m_gameCameras.emplace_back(_viewport, _near, _far,
                               m_ownerWorld.GetApplication().GetMessageBus());
  }
  else
  {
    m_gameCameras.emplace_back(_viewport, _near, _far);
  }
  return m_gameCameras.size() - 1;
}

// ------------------------------------------------------------------------------

void RenderWorld::RenderScene(float _interpolation)
{
  m_renderDevice.ClearBuffer(graphics::RendererBufferType::Color_Depth);

  for (const auto& camera : m_gameCameras)
  {
    graphics::GLFramebuffer2D* target = camera.GetRenderTarget();
    if (target != nullptr)
    {
      target->Bind();
      target->Clear();
    }
    else
    {
      const math::Vec4i32& viewport = camera.GetViewport();
      m_renderDevice.SetViewport(viewport[0], viewport[1], viewport[2],
                                 viewport[3]);
    }

    for (auto&& system : m_renderingSystems)
    {
      system->Render(m_ownerWorld, camera, _interpolation);
    }

    if (target != nullptr)
    {
      target->Unbind();
    }
  }
}

// ------------------------------------------------------------------------------

void RenderWorld::ApplyPostProcesses()
{
  m_renderDevice.SetDepthTesting(false);
  m_renderDevice.SetCulling(false);

  for (const auto& camera : m_gameCameras)
  {
    const math::Vec4i32& viewport = camera.GetViewport();
    graphics::GLFramebuffer2D* source = camera.GetRenderTarget();

    if (source == nullptr)
    {
      continue;
    }

    graphics::GLFramebuffer2D output(source->GetWidth(), source->GetHeight());

    for (auto&& postProcessEffect : m_postProcesses)
    {
      postProcessEffect->Execute(*source, output);

      // Copy back into source to be up-to-date for next process
      m_copyToTargetPass.Execute(output, *source);
    }

    m_renderDevice.SetViewport(viewport[0], viewport[1], viewport[2],
                               viewport[3]);

    // Render To Screen
    m_copyToTargetPass.Execute(output, output);
  }
}

// ------------------------------------------------------------------------------

void RenderWorld::RenderGUI(float _interpolation)
{
  const math::Vec4i32& viewport = m_screenCamera.GetViewport();
  // Screen camera's viewport is ordered differently, because its origin is
  // top left to match the screen origin.
  std::uint32_t x = viewport[0];
  std::uint32_t y = viewport[3];
  std::uint32_t width = viewport[2];
  std::uint32_t height = viewport[1];

  m_renderDevice.SetViewport(x, y, width, height);

  for (auto&& system : m_guiSystems)
  {
    system->Render(m_ownerWorld, m_screenCamera, _interpolation);
  }

  m_renderDevice.SetDepthTesting(true);
  m_renderDevice.SetCulling(true);
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage