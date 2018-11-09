#include "renderer/GLTexture2D.h"

#include "renderer/GLCommon.h"
#include <exceptions/RuntimeError.h>

#include <glew.h>
#include <stb_image.h>

namespace mage
{
namespace renderer
{

namespace
{

// ------------------------------------------------------------------------------

GLenum GetGLTextureWrap(TextureWrap _wrap)
{
  switch (_wrap)
  {
    case TextureWrap::Clamp:
      return GL_CLAMP;
    case TextureWrap::ClampToBorder:
      return GL_CLAMP_TO_BORDER;
    case TextureWrap::ClampToEdge:
      return GL_CLAMP_TO_EDGE;
    case TextureWrap::Repeat:
      return GL_REPEAT;
    case TextureWrap::MirroredRepeat:
      return GL_MIRRORED_REPEAT;
  }

  return 0;
}

// ------------------------------------------------------------------------------

GLenum GetGLTextureFormat(TextureFormat _format)
{
  switch (_format)
  {
    case TextureFormat::RGBA:
      return GL_RGBA;
    case TextureFormat::RGB:
      return GL_RGB;
    case TextureFormat::Luminance:
      return GL_LUMINANCE;
    case TextureFormat::LuminanceAlpha:
      return GL_LUMINANCE_ALPHA;
  }

  return 0;
}

// ------------------------------------------------------------------------------

GLenum GetGLTextureFilter(TextureFilter _filter)
{
  switch (_filter)
  {
    case TextureFilter::Linear:
      return GL_LINEAR;
    case TextureFilter::Nearest:
      return GL_NEAREST;
  }

  return 0;
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

TextureParameters::TextureParameters()
    : m_format(TextureFormat::RGBA)
    , m_filter(TextureFilter::Linear)
    , m_wrap(TextureWrap::Clamp)
{
}

// ------------------------------------------------------------------------------

TextureParameters::TextureParameters(TextureFormat _format,
                                     TextureFilter _filter, TextureWrap _wrap)
    : m_format(_format)
    , m_filter(_filter)
    , m_wrap(_wrap)
{
}

// ------------------------------------------------------------------------------

GLTexture2D::GLTexture2D(const std::string& _filepath,
                         TextureParameters _parameters)
    : m_handle(0)
{
  LoadTexture(_filepath, _parameters);
}

// ------------------------------------------------------------------------------

GLTexture2D::~GLTexture2D() { GLCall(glDeleteTextures(1, &m_handle)); }

// ------------------------------------------------------------------------------

void GLTexture2D::LoadTexture(const std::string& _filepath,
                              TextureParameters _parameters)
{
  std::int32_t width = 0;
  std::int32_t height = 0;
  std::int32_t channels = 0;

  std::int32_t desiredChannels = 4;
  if (_parameters.m_format == TextureFormat::RGB)
  {
    desiredChannels = 3;
  }

  unsigned char* data =
      stbi_load(_filepath.c_str(), &width, &height, &channels, desiredChannels);

  if (data == nullptr)
  {
    throw RUNTIME_ERROR("Could not load image " + _filepath);
  }

  GLCall(glGenTextures(1, &m_handle));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_handle));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                         GetGLTextureFilter(_parameters.m_filter)));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                         GetGLTextureFilter(_parameters.m_filter)));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                         GetGLTextureWrap(_parameters.m_wrap)));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                         GetGLTextureWrap(_parameters.m_wrap)));

  GLCall(glTexImage2D(
      GL_TEXTURE_2D, 0, GetGLTextureFormat(_parameters.m_format), width, height,
      0, GetGLTextureFormat(_parameters.m_format), GL_UNSIGNED_BYTE, data));

  free(data);

  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

// ------------------------------------------------------------------------------

void GLTexture2D::Bind(std::uint32_t _slot) const
{
  GLCall(glActiveTexture(GL_TEXTURE0 + _slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_handle));
}

// ------------------------------------------------------------------------------

void GLTexture2D::Unbind(std::uint32_t _slot) const
{
  GLCall(glActiveTexture(GL_TEXTURE0 + _slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_handle));
}

// ------------------------------------------------------------------------------

bool GLTexture2D::operator==(const GLTexture2D& _other) const
{
  return m_handle == _other.m_handle;
}

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage