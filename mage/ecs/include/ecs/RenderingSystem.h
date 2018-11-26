#pragma once

#include "System.h"

#include "graphics/Camera.h"
#include "renderer/GLShader.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The rendering system describes a system which is called as frequently as
/// possible. It should handle rendering of the game state using the shader it
/// holds. Each rendering system has its own shader, because each entity that is
/// rendered by a certain system will most likely all want the same shader
/// effect.
/////////////////////////////////////////////////
class RenderingSystem : public System
{
public:
  RenderingSystem(graphics::GLShader _shader);
  virtual ~RenderingSystem();

  virtual void Render(World& _world, const graphics::Camera& _camera,
                      float _deltaTime) = 0;

protected:
  graphics::GLShader
      m_shader; ///< the shader to be used for the rendering process
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage