#include "renderer/GLTextureCube.h"

#include "exceptions/RuntimeError.h"
#include "renderer/GLCommon.h"

#include <GLEW/glew.h>
#include <stb/stb_image.h>

namespace mage
{
namespace graphics
{
// ------------------------------------------------------------------------------

GLTextureCube::GLTextureCube(std::string* _sixSkyboxFiles)
    : m_handle(0)
{
  LoadTexture(_sixSkyboxFiles);
}

// ------------------------------------------------------------------------------

GLTextureCube::~GLTextureCube()
{
  if (m_handle != 0)
  {
    GLCall(glDeleteTextures(1, &m_handle));
    m_handle = 0;
  }
}

// ------------------------------------------------------------------------------

GLTextureCube::GLTextureCube(GLTextureCube&& _moved)
    : m_handle(std::move(_moved.m_handle))
{
  _moved.m_handle = 0;
}

// ------------------------------------------------------------------------------

GLTextureCube& GLTextureCube::operator=(GLTextureCube&& _moved)
{
  m_handle = std::move(_moved.m_handle);
  _moved.m_handle = 0;
  return *this;
}

// ------------------------------------------------------------------------------

void GLTextureCube::Bind(std::uint32_t _slot) const
{
  GLCall(glActiveTexture(GL_TEXTURE0 + _slot));
  GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle));
}

// ------------------------------------------------------------------------------

void GLTextureCube::Unbind(std::uint32_t _slot) const
{
  GLCall(glActiveTexture(GL_TEXTURE0 + _slot));
  GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

// ------------------------------------------------------------------------------

bool GLTextureCube::operator==(const GLTextureCube& _other) const
{
  return m_handle == _other.m_handle;
}

// ------------------------------------------------------------------------------

void GLTextureCube::LoadTexture(std::string* _sixSkyboxFiles)
{
  GLCall(glGenTextures(1, &m_handle));
  GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle));

  std::int32_t width = 0;
  std::int32_t height = 0;
  std::int32_t channels = 0;
  std::int32_t desiredChannels = 4;

  for (size_t i = 0; i < 6; i++)
  {
    const std::string& imageFile = _sixSkyboxFiles[i];

    unsigned char* data = stbi_load(imageFile.c_str(), &width, &height,
                                    &channels, desiredChannels);

    if (data == nullptr)
    {
      stbi_image_free(data);
      throw RUNTIME_ERROR("Could not load filepath " + imageFile);
    }

    GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,
                        height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

    stbi_image_free(data);
  }

  GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                         GL_LINEAR_MIPMAP_LINEAR));
  GLCall(
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
                         GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
                         GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,
                         GL_CLAMP_TO_EDGE));

  GLCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
  GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage