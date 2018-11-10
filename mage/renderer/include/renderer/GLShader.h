#pragma once

#include <cstdint>
#include <string>

#include <math/Mat.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

enum class ShaderType
{
  Vertex,
  Fragment
};

// ------------------------------------------------------------------------------

class GLShader
{
public:
  GLShader(const std::string& _vsFilePath, const std::string& _fsFilePath);
  ~GLShader();

  // ------------------------------------------------------------------------------

  void Bind() const;

  // ------------------------------------------------------------------------------

  void Unbind() const;

  // ------------------------------------------------------------------------------

  void SetUniform1f(const std::string& _name, float _value);
  void SetUniform1fv(const std::string& _name, float* _value,
                     std::int32_t _count);
  void SetUniform1i(const std::string& _name, std::int32_t _value);
  void SetUniform1iv(const std::string& _name, std::int32_t* _value,
                     std::int32_t _count);
  void SetUniform2f(const std::string& _name, const math::Vec2f& _vector);
  void SetUniform3f(const std::string& _name, const math::Vec3f& _vector);
  void SetUniform4f(const std::string& _name, const math::Vec4f& _vector);
  void SetUniformMat4(const std::string& _name, math::Mat4f& _matrix);

  // ------------------------------------------------------------------------------

  void SetUniform1f(std::uint32_t _location, float _value);
  void SetUniform1fv(std::uint32_t _location, float* _value,
                     std::int32_t _count);
  void SetUniform1i(std::uint32_t _location, std::int32_t _value);
  void SetUniform1iv(std::uint32_t _location, std::int32_t* _value,
                     std::int32_t _count);
  void SetUniform2f(std::uint32_t _location, const math::Vec2f& _vector);
  void SetUniform3f(std::uint32_t _location, const math::Vec3f& _vector);
  void SetUniform4f(std::uint32_t _location, const math::Vec4f& _vector);
  void SetUniformMat4(std::uint32_t _location, math::Mat4f& _matrix);

  // ------------------------------------------------------------------------------

  bool operator==(const GLShader& _other) const;

  // ------------------------------------------------------------------------------

private:
  std::uint32_t CompileShader(const char* _source, ShaderType _type);

  // ------------------------------------------------------------------------------

  void LinkShaders(std::uint32_t _vsShaderHandle,
                   std::uint32_t _fsShaderHandle);

  // ------------------------------------------------------------------------------

  std::int32_t GetUniformLocation(const std::string& _name);

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_programHandle;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage