#pragma once

#include "renderer/GLShader.h"

#include <memory>
#include <vector>

namespace mage
{
namespace graphics
{

class ShaderLibrary
{
public:
  ShaderLibrary();
  ~ShaderLibrary();

  std::shared_ptr<GLShader> Get(const std::string& _vsFilePath,
                                const std::string& _fsFilePath);

  void Clear();
  void Refresh();

private:
  struct ShaderResourceInstance
  {
    ShaderResourceInstance(std::shared_ptr<GLShader>&& _shader,
                           std::uint32_t _hashedName);

    std::shared_ptr<GLShader> m_shader;
    std::uint32_t m_hashedName;
  };

  std::vector<ShaderResourceInstance> m_loadedShaders;
};

} // namespace graphics
} // namespace mage