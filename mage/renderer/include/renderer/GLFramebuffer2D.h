#pragma once

#include "GLTexture2D.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class GLFramebuffer2D
{
public:
  GLFramebuffer2D(std::uint32_t _width, std::uint32_t _height);
  ~GLFramebuffer2D();

  GLFramebuffer2D(const GLFramebuffer2D& _copy) = delete;
  GLFramebuffer2D(GLFramebuffer2D&& _moved);

  GLFramebuffer2D& operator=(const GLFramebuffer2D& _copy) = delete;
  GLFramebuffer2D& operator=(GLFramebuffer2D&& _moved);

  void Bind() const;
  void Unbind() const;
  void Clear() const;

  inline std::uint32_t GetWidth() const { return m_width; }
  inline std::uint32_t GetHeight() const { return m_height; }

  inline const GLTexture2D& GetTexture() const { return m_texture; }

private:
  std::uint32_t m_framebufferHandle;
  std::uint32_t m_depthbufferHandle;

  std::uint32_t m_width;
  std::uint32_t m_height;

  GLTexture2D m_texture;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage