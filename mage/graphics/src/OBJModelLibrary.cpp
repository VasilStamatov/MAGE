#include "graphics/OBJModelLibrary.h"

#include <algorithm>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

OBJModelLibrary::OBJModelLibrary()
    : m_loadedMeshes()
{
}

// ------------------------------------------------------------------------------

OBJModelLibrary::~OBJModelLibrary() {}

// ------------------------------------------------------------------------------

std::shared_ptr<OBJModel> OBJModelLibrary::Get(const std::string& _filepath)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_filepath);

  auto foundIt =
      std::find_if(m_loadedMeshes.begin(), m_loadedMeshes.end(),
                   [hashedName](const MeshResourceInstance& _resource) {
                     return _resource.m_hashedName == hashedName;
                   });
  ;

  if (foundIt != m_loadedMeshes.end())
  {
    return foundIt->m_staticMesh;
  }

  m_loadedMeshes.emplace_back(std::make_shared<OBJModel>(_filepath),
                              hashedName);

  return m_loadedMeshes.back().m_staticMesh;
}

// ------------------------------------------------------------------------------

void OBJModelLibrary::Clear() { m_loadedMeshes.clear(); }

// ------------------------------------------------------------------------------

void OBJModelLibrary::Refresh()
{
  // clear loaded textures which aren't referenced anywhere
  m_loadedMeshes.erase(
      std::remove_if(m_loadedMeshes.begin(), m_loadedMeshes.end(),
                     [](const MeshResourceInstance& _resource) -> bool {
                       return _resource.m_staticMesh.use_count() == 1;
                     }),
      m_loadedMeshes.end());
}

// ------------------------------------------------------------------------------

OBJModelLibrary::MeshResourceInstance::MeshResourceInstance(
    std::shared_ptr<OBJModel>&& _texture, std::uint32_t _hashedName)
    : m_staticMesh(std::move(_texture))
    , m_hashedName(_hashedName)
{
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage