#include "renderer/GLShader.h"

#include "exceptions/RuntimeError.h"
#include "filesystem/Filesystem.h"
#include "renderer/GLCommon.h"

#include <vector>

#include <glew.h>

namespace mage
{
namespace graphics
{

namespace
{

// ------------------------------------------------------------------------------

GLenum GetShaderType(ShaderType _type)
{
  switch (_type)
  {
    case ShaderType::Vertex:
      return GL_VERTEX_SHADER;
    case ShaderType::Fragment:
      return GL_FRAGMENT_SHADER;
  }

  assert(false);
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

GLShader::GLShader(const std::string& _vsFilePath,
                   const std::string& _fsFilePath)
{
  GLCall(m_programHandle = glCreateProgram());

  std::string vsSource;
  std::string fsSource;

  filesystem::ReadFileToBuffer(_vsFilePath, vsSource);
  filesystem::ReadFileToBuffer(_fsFilePath, fsSource);

  std::uint32_t vsShaderHandle =
      CompileShader(vsSource.c_str(), ShaderType::Vertex);

  std::uint32_t fsShaderHandle =
      CompileShader(fsSource.c_str(), ShaderType::Fragment);

  LinkShaders(vsShaderHandle, fsShaderHandle);
}

// ------------------------------------------------------------------------------

GLShader::~GLShader()
{
  if (m_programHandle != 0)
  {
    GLCall(glDeleteProgram(m_programHandle));
    m_programHandle = 0;
  }
}

// ------------------------------------------------------------------------------

GLShader::GLShader(GLShader&& _moved)
    : m_programHandle(std::move(_moved.m_programHandle))
{
  _moved.m_programHandle = 0;
}

// ------------------------------------------------------------------------------

GLShader& GLShader::operator=(GLShader&& _moved)
{
  m_programHandle = std::move(_moved.m_programHandle);
  _moved.m_programHandle = 0;
  return *this;
}

// ------------------------------------------------------------------------------

void GLShader::Bind() const { GLCall(glUseProgram(m_programHandle)); }

// ------------------------------------------------------------------------------

void GLShader::Unbind() const { GLCall(glUseProgram(0)); }

// ------------------------------------------------------------------------------

void GLShader::SetUniform1f(const std::string& _name, float _value)
{
  SetUniform1f(GetUniformLocation(_name), _value);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1fv(const std::string& _name, float* _value,
                             std::int32_t _count)
{
  SetUniform1fv(GetUniformLocation(_name), _value, _count);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1i(const std::string& _name, std::int32_t _value)
{
  SetUniform1i(GetUniformLocation(_name), _value);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1iv(const std::string& _name, std::int32_t* _value,
                             std::int32_t _count)
{
  SetUniform1iv(GetUniformLocation(_name), _value, _count);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform2f(const std::string& _name,
                            const math::Vec2f& _vector)
{
  SetUniform2f(GetUniformLocation(_name), _vector);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform3f(const std::string& _name,
                            const math::Vec3f& _vector)
{
  SetUniform3f(GetUniformLocation(_name), _vector);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform4f(const std::string& _name,
                            const math::Vec4f& _vector)
{
  SetUniform4f(GetUniformLocation(_name), _vector);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniformMat4(const std::string& _name, math::Mat4f& _matrix)
{
  SetUniformMat4(GetUniformLocation(_name), _matrix);
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1f(std::uint32_t _location, float _value)
{
  GLCall(glUniform1f(_location, _value));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1fv(std::uint32_t _location, float* _value,
                             std::int32_t _count)
{
  GLCall(glUniform1fv(_location, _count, _value));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1i(std::uint32_t _location, std::int32_t _value)
{
  GLCall(glUniform1i(_location, _value));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform1iv(std::uint32_t _location, std::int32_t* _value,
                             std::int32_t _count)
{
  GLCall(glUniform1iv(_location, _count, _value));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform2f(std::uint32_t _location, const math::Vec2f& _vector)
{
  GLCall(glUniform2f(_location, _vector[0], _vector[1]));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform3f(std::uint32_t _location, const math::Vec3f& _vector)
{
  GLCall(glUniform3f(_location, _vector[0], _vector[1], _vector[2]));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniform4f(std::uint32_t _location, const math::Vec4f& _vector)
{
  GLCall(
      glUniform4f(_location, _vector[0], _vector[1], _vector[2], _vector[3]));
}

// ------------------------------------------------------------------------------

void GLShader::SetUniformMat4(std::uint32_t _location, math::Mat4f& _matrix)
{
  // Transpose flag is set to GL_TRUE, because the matrix class is row-major
  GLCall(glUniformMatrix4fv(_location, 1, GL_TRUE, &_matrix[0]));
}

// ------------------------------------------------------------------------------

std::uint32_t GLShader::CompileShader(const char* _source, ShaderType _type)
{
  GLCall(std::uint32_t shaderId = glCreateShader(GetShaderType(_type)));

  if (shaderId == 0)
  {
    throw RUNTIME_ERROR("Failed to create shader");
  }

  GLCall(glShaderSource(shaderId, 1, &_source, nullptr));

  GLCall(glCompileShader(shaderId));

  // check for errors
  GLint success = 0;
  GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));

  if (success == GL_FALSE)
  {
    GLint maxLength = 0;
    GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength));

    std::vector<char> errorLog(maxLength);
    GLCall(glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]));

    GLCall(glDeleteShader(shaderId));

    std::printf("Shader Compilation %s\n", &(errorLog[0]));
    throw RUNTIME_ERROR("Shader failed to compile");
  }

  return shaderId;
}

// ------------------------------------------------------------------------------

void GLShader::LinkShaders(std::uint32_t _vsShaderHandle,
                           std::uint32_t _fsShaderHandle)
{
  GLCall(glAttachShader(m_programHandle, _vsShaderHandle));
  GLCall(glAttachShader(m_programHandle, _fsShaderHandle));

  GLCall(glBindAttribLocation(m_programHandle, 0, "in_Position"));
  GLCall(glBindAttribLocation(m_programHandle, 1, "in_Normal"));
  GLCall(glBindAttribLocation(m_programHandle, 2, "in_Color"));
  GLCall(glBindAttribLocation(m_programHandle, 3, "in_TexCoord"));

  GLCall(glLinkProgram(m_programHandle));

  GLint isLinked = 0;
  GLCall(glGetProgramiv(m_programHandle, GL_LINK_STATUS, (int*)&isLinked));

  if (isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    GLCall(glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &maxLength));

    std::vector<char> errorLog(maxLength);
    GLCall(glGetProgramInfoLog(m_programHandle, maxLength, &maxLength,
                               &errorLog[0]));

    GLCall(glDeleteProgram(m_programHandle));

    GLCall(glDeleteShader(_vsShaderHandle));
    GLCall(glDeleteShader(_fsShaderHandle));

    // print the error log and quit
    std::printf("Shader Linking %s\n", &errorLog[0]);
    throw RUNTIME_ERROR("Shaders failed to link!");
  }

  // Always detach shaders after a successful link.
  GLCall(glDetachShader(m_programHandle, _vsShaderHandle));
  GLCall(glDetachShader(m_programHandle, _fsShaderHandle));
  GLCall(glDeleteShader(_vsShaderHandle));
  GLCall(glDeleteShader(_fsShaderHandle));
}

// ------------------------------------------------------------------------------

std::int32_t GLShader::GetUniformLocation(const std::string& _name)
{
  GLCall(GLint result = glGetUniformLocation(m_programHandle, _name.c_str()));

  if (result == -1)
  {
    throw RUNTIME_ERROR("Shader could not find uniform " + _name);
  }

  return result;
}

// ------------------------------------------------------------------------------

bool GLShader::operator==(const GLShader& _other) const
{
  return m_programHandle == _other.m_programHandle;
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage
