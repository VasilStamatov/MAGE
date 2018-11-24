#include "graphics/ShaderLibrary.h"

#include <algorithm>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

ShaderLibrary::ShaderLibrary()
    : m_loadedShaders()
{
}

// ------------------------------------------------------------------------------

ShaderLibrary::~ShaderLibrary() {}

// ------------------------------------------------------------------------------

std::shared_ptr<GLShader> ShaderLibrary::Get(const std::string& _vsFilePath,
                                             const std::string& _fsFilePath)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_vsFilePath + _fsFilePath);

  auto foundIt =
      std::find_if(m_loadedShaders.begin(), m_loadedShaders.end(),
                   [hashedName](const ShaderResourceInstance& _resource) {
                     return _resource.m_hashedName == hashedName;
                   });

  if (foundIt != m_loadedShaders.end())
  {
    return foundIt->m_shader;
  }

  m_loadedShaders.emplace_back(
      std::make_shared<GLShader>(_vsFilePath, _fsFilePath), hashedName);

  return m_loadedShaders.back().m_shader;
}

// ------------------------------------------------------------------------------

void ShaderLibrary::Clear() { m_loadedShaders.clear(); }

// ------------------------------------------------------------------------------

void ShaderLibrary::Refresh()
{
  // Clear loaded shaders which aren't referenced
  m_loadedShaders.erase(
      std::remove_if(m_loadedShaders.begin(), m_loadedShaders.end(),
                     [](const ShaderResourceInstance& _resource) -> bool {
                       return _resource.m_shader.use_count() == 1;
                     }),
      m_loadedShaders.end());
}

// ------------------------------------------------------------------------------

ShaderLibrary::ShaderResourceInstance::ShaderResourceInstance(
    std::shared_ptr<GLShader>&& _shader, std::uint32_t _hashedName)
    : m_shader(std::move(_shader))
    , m_hashedName(_hashedName)
{
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage