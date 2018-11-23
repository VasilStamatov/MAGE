#pragma once

#include "renderer/GLFramebuffer2D.h"
#include "renderer/GLIndexBuffer.h"
#include "renderer/GLShader.h"
#include "renderer/GLVertexArray.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class PostProcessPass
{
public:
  PostProcessPass(GLShader _postProcessShader);
  virtual ~PostProcessPass();

  virtual void Apply(GLFramebuffer2D& _source, GLFramebuffer2D* _target) = 0;

protected:
  GLShader m_shader;

  GLVertexArray m_screenVAO;
  GLVertexBuffer m_screenVBO;
  GLIndexBuffer m_screenIBO;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage