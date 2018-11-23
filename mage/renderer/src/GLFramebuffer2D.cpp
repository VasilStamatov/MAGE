#include "renderer/GLFramebuffer2D.h"

#include "exceptions/RuntimeError.h"
#include "renderer/GLCommon.h"

#include <GLEW/glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

GLFramebuffer2D::GLFramebuffer2D(std::uint32_t _width, std::uint32_t _height)
    : m_framebufferHandle(0)
    , m_depthbufferHandle(0)
    , m_width(_width)
    , m_height(_height)
    , m_texture(_width, _height)
{
  GLCall(glGenFramebuffers(1, &m_framebufferHandle));
  GLCall(glGenRenderbuffers(1, &m_depthbufferHandle));

  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthbufferHandle));
  GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width,
                               m_height));

  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle));

  GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                GL_TEXTURE_2D, m_texture.GetHandle(), 0));
  GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_RENDERBUFFER, m_depthbufferHandle));

  GLCall(auto glFramebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER));

  if (glFramebufferStatus != GL_FRAMEBUFFER_COMPLETE)
  {
    throw RUNTIME_ERROR("Failed to complete framebuffer initialization!");
  }

  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

// ------------------------------------------------------------------------------

GLFramebuffer2D::~GLFramebuffer2D()
{
  if (m_framebufferHandle != 0)
  {
    GLCall(glDeleteFramebuffers(1, &m_framebufferHandle));
  }
  if (m_depthbufferHandle != 0)
  {
    GLCall(glDeleteRenderbuffers(1, &m_depthbufferHandle));
  }
}

// ------------------------------------------------------------------------------

GLFramebuffer2D::GLFramebuffer2D(GLFramebuffer2D&& _moved)
    : m_framebufferHandle(std::move(_moved.m_framebufferHandle))
    , m_depthbufferHandle(std::move(_moved.m_depthbufferHandle))
    , m_width(std::move(_moved.m_width))
    , m_height(std::move(_moved.m_height))
    , m_texture(std::move(_moved.m_texture))
{
  _moved.m_framebufferHandle = 0;
  _moved.m_depthbufferHandle = 0;
}

// ------------------------------------------------------------------------------

GLFramebuffer2D& GLFramebuffer2D::operator=(GLFramebuffer2D&& _moved)
{
  m_framebufferHandle = std::move(_moved.m_framebufferHandle);
  m_depthbufferHandle = std::move(_moved.m_depthbufferHandle);
  m_width = std::move(_moved.m_width);
  m_height = std::move(_moved.m_height);
  m_texture = std::move(_moved.m_texture);

  _moved.m_framebufferHandle = 0;
  _moved.m_depthbufferHandle = 0;

  return *this;
}

// ------------------------------------------------------------------------------

void GLFramebuffer2D::Bind() const
{
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle));
  GLCall(glViewport(0, 0, m_width, m_height));
}

// ------------------------------------------------------------------------------

void GLFramebuffer2D::Unbind() const
{
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

// ------------------------------------------------------------------------------

void GLFramebuffer2D::Clear() const
{
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage