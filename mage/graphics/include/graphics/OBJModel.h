#pragma once

#include "math/AABB.h"

#include <string>
#include <vector>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

struct Vertex
{
  bool operator==(const Vertex& _other) const
  {
    return m_pos == _other.m_pos && m_color == _other.m_color &&
           m_texCoords == _other.m_texCoords && m_normal == _other.m_normal;
  }

  math::Vec3f m_pos;
  math::Vec3f m_normal;
  math::Vec3f m_color;
  math::Vec2f m_texCoords;
};

// ------------------------------------------------------------------------------

class OBJModel
{
public:
  OBJModel(const std::string& _objFile);

  std::vector<Vertex>& GetVertices();
  std::vector<std::uint32_t>& GetIndices();
  math::AABB& GetAABB();

private:
  std::vector<Vertex> m_vertices;
  std::vector<std::uint32_t> m_indices;
  math::AABB m_AABB;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage