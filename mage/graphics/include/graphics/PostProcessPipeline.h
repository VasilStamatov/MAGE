#pragma once

#include "renderer/GLFramebuffer2D.h"
#include "renderer/GLIndexBuffer.h"
#include "renderer/GLShader.h"
#include "renderer/GLVertexArray.h"

#include <vector>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class PostProcessPipeline
{
public:
  PostProcessPipeline();

  virtual void Execute(GLFramebuffer2D& _source, GLFramebuffer2D& _target) = 0;

protected:
  GLVertexArray m_screenVAO;
  GLVertexBuffer m_screenVBO;
  GLIndexBuffer m_screenIBO;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage