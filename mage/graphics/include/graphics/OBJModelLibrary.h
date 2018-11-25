#pragma once

#include "OBJModel.h"

#include <memory>
#include <vector>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class OBJModelLibrary
{
public:
  OBJModelLibrary();
  ~OBJModelLibrary();

  // ------------------------------------------------------------------------------

  std::shared_ptr<OBJModel> Get(const std::string& _filepath);

  // ------------------------------------------------------------------------------

  void Clear();
  void Refresh();

  // ------------------------------------------------------------------------------

private:
  struct MeshResourceInstance
  {
    MeshResourceInstance(std::shared_ptr<OBJModel>&& _texture,
                         std::uint32_t _hashedName);

    std::shared_ptr<OBJModel> m_staticMesh;
    std::uint32_t m_hashedName;
  };

  // ------------------------------------------------------------------------------

  std::vector<MeshResourceInstance> m_loadedMeshes;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage