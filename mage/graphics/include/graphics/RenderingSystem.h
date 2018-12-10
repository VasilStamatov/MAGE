#pragma once

#include "Camera.h"

#include "ecs/System.h"
#include "renderer/GLShader.h"
#include "renderer/RenderDevice.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The rendering system describes a system which is called as frequently as
/// possible. It should handle rendering of the game state using the shader it
/// holds. Each rendering system has its own shader, because each entity that is
/// rendered by a certain system will most likely all want the same shader
/// effect.
/////////////////////////////////////////////////
class RenderingSystem : public ecs::System
{
public:
  RenderingSystem(GLShader _shader, RenderDevice& _renderDevice);
  virtual ~RenderingSystem();

  virtual void Render(core::World& _world, const Camera& _camera,
                      float _deltaSeconds) = 0;

protected:
  GLShader m_shader; ///< the shader to be used for the rendering process
  RenderDevice& m_renderDevice;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage