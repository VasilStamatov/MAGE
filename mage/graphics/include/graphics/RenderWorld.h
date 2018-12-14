#pragma once

#include "CopyToTargetPipeline.h"
#include "OBJModelLibrary.h"
#include "RenderingSystem.h"
#include "Texture2DLibrary.h"

#include "renderer/RenderDevice.h"

namespace mage
{
namespace graphics
{

/////////////////////////////////////////////////
/// The render world which contains the systems and all other required data for
/// the render pipeline
/////////////////////////////////////////////////
class RenderWorld
{
public:
  RenderWorld(RenderDevice& _renderDevice, core::World& _ownerWorld);
  ~RenderWorld();

  // ------------------------------------------------------------------------------

  void Initialize();
  void Uninitialize();

  // ------------------------------------------------------------------------------

  void Render(float _interpolation);

  // ------------------------------------------------------------------------------

  void UpdateEntityStatus(ecs::Entity& _entity,
                          ecs::ComponentMask _entitySignature);

  // ------------------------------------------------------------------------------

  void AddRenderingSystem(std::unique_ptr<RenderingSystem> _system);

  // ------------------------------------------------------------------------------

  void AddPostProcessPipeline(std::unique_ptr<PostProcessPipeline> _pipeline);

  // ------------------------------------------------------------------------------

  void AddGUISystem(std::unique_ptr<RenderingSystem> _system);

  /////////////////////////////////////////////////
  /// Adds a perspective camera to the world. This doesn't need to be explicitly
  /// called as it's done whenver a camera component is added. This is only
  /// needed if a camera component is not required.
  /////////////////////////////////////////////////
  std::uint32_t AddPerspectiveCamera(const math::Vec4i32& _viewport,
                                     float _fovDegrees, float _near, float _far,
                                     bool _listenForWindowResize);

  /////////////////////////////////////////////////
  /// Adds an orthographic camera to the world. This doesn't need to be
  /// explicitly called as it's done whenver a camera component is added. This
  /// is only needed if a camera component is not required.
  /////////////////////////////////////////////////
  std::uint32_t AddOrthographicCamera(const math::Vec4i32& _viewport,
                                      float _near, float _far,
                                      bool _listenForWindowResize);

  inline Camera& GetGameCamera(std::uint32_t _index)
  {
    assert(_index < m_gameCameras.size());
    return m_gameCameras[_index];
  }
  inline const math::Vec4i32& GetScreenViewport()
  {
    return m_screenCamera.GetViewport();
  }
  inline OBJModelLibrary& GetOBJModelLibrary() { return m_objModelLibrary; }
  inline Texture2DLibrary& GetTexture2DLibrary() { return m_textureLibrary; }

private:
  void RenderScene(float _interpolation);
  void ApplyPostProcesses();
  void RenderGUI(float _interpolation);

private:
  std::vector<std::unique_ptr<RenderingSystem>> m_renderingSystems;
  std::vector<std::unique_ptr<PostProcessPipeline>> m_postProcesses;
  std::vector<std::unique_ptr<RenderingSystem>> m_guiSystems;

  std::vector<Camera> m_gameCameras;
  Camera m_screenCamera;

  CopyToTargetPipeline m_copyToTargetPass;

  Texture2DLibrary m_textureLibrary;
  OBJModelLibrary m_objModelLibrary;

  RenderDevice& m_renderDevice;
  core::World& m_ownerWorld;
};

} // namespace graphics
} // namespace mage