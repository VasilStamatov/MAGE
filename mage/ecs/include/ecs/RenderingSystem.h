#pragma once

#include "System.h"

#include "graphics/Camera.h"
#include "renderer/GLShader.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class RenderingSystem : public System
{
public:
  RenderingSystem(graphics::GLShader _shader);
  virtual ~RenderingSystem();

  virtual void Render(World& _world, const graphics::Camera& _camera,
                      float _deltaTime) = 0;

protected:
  graphics::GLShader m_shader;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage