#include "renderer/GLTexture2D.h"

#include "exceptions/RuntimeError.h"
#include "renderer/GLCommon.h"

#include <GLEW/glew.h>
#include <stb/stb_image.h>

namespace mage
{
namespace graphics
{

namespace
{

// ------------------------------------------------------------------------------

GLenum GetGLTextureWrap(TextureWrap _wrap)
{
  switch (_wrap)
  {
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
    , m_wrap(TextureWrap::ClampToEdge)
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

GLTexture2D::GLTexture2D(std::uint32_t _width, std::uint32_t _height,
                         TextureParameters _parameters)
    : m_handle(0)
{
  GenTexture(_width, _height, nullptr, _parameters);
}

// ------------------------------------------------------------------------------

GLTexture2D::GLTexture2D(const std::string& _filepath,
                         TextureParameters _parameters)
    : m_handle(0)
{
  LoadTexture(_filepath, _parameters);
}

// ------------------------------------------------------------------------------

GLTexture2D::~GLTexture2D()
{
  if (m_handle != 0)
  {
    GLCall(glDeleteTextures(1, &m_handle));
    m_handle = 0;
  }
}

// ------------------------------------------------------------------------------

GLTexture2D::GLTexture2D(GLTexture2D&& _moved)
    : m_handle(std::move(_moved.m_handle))
{
  _moved.m_handle = 0;
}

// ------------------------------------------------------------------------------

GLTexture2D& GLTexture2D::operator=(GLTexture2D&& _moved)
{
  m_handle = std::move(_moved.m_handle);
  _moved.m_handle = 0;
  return *this;
}

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

  stbi_set_flip_vertically_on_load(true);
  unsigned char* data =
      stbi_load(_filepath.c_str(), &width, &height, &channels, desiredChannels);

  if (data == nullptr)
  {
    throw RUNTIME_ERROR("Could not load image " + _filepath);
  }

  GenTexture(width, height, data, _parameters);

  free(data);
}

// ------------------------------------------------------------------------------

void GLTexture2D::GenTexture(uint32_t _width, std::uint32_t _height,
                             std::uint8_t* _data, TextureParameters _parameters)
{
  GLCall(glGenTextures(1, &m_handle));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_handle));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                         _parameters.m_filter == TextureFilter::Linear
                             ? GL_LINEAR_MIPMAP_LINEAR
                             : GL_NEAREST));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                         GetGLTextureFilter(_parameters.m_filter)));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                         GetGLTextureWrap(_parameters.m_wrap)));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                         GetGLTextureWrap(_parameters.m_wrap)));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0,
                      GetGLTextureFormat(_parameters.m_format), _width, _height,
                      0, GetGLTextureFormat(_parameters.m_format),
                      GL_UNSIGNED_BYTE, _data));

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

} // namespace graphics
} // namespace mage