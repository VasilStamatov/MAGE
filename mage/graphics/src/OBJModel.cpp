#include "graphics/OBJModel.h"

#include "exceptions/RuntimeError.h"

#include <tinyobj/tiny_obj_loader.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

OBJModel::OBJModel(const std::string& _objFile)
    : m_AABB(math::Vec3f(0.0f), math::Vec3f(0.0f))
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                        _objFile.c_str()))
  {
    throw RUNTIME_ERROR(warn + err);
  }

  for (const auto& shape : shapes)
  {
    for (const auto& index : shape.mesh.indices)
    {
      Vertex vertex;

      vertex.m_pos[0] = attrib.vertices[3 * index.vertex_index + 0];
      vertex.m_pos[1] = attrib.vertices[3 * index.vertex_index + 1];
      vertex.m_pos[2] = attrib.vertices[3 * index.vertex_index + 2];

      vertex.m_texCoords[0] = attrib.texcoords[2 * index.texcoord_index + 0];
      vertex.m_texCoords[1] = attrib.texcoords[2 * index.texcoord_index + 1];

      vertex.m_normal[0] = attrib.normals[3 * index.normal_index + 0];
      vertex.m_normal[1] = attrib.normals[3 * index.normal_index + 1];
      vertex.m_normal[2] = attrib.normals[3 * index.normal_index + 2];

      // check if vertex doesn't exist
      auto foundIt = std::find(m_vertices.begin(), m_vertices.end(), vertex);
      if (foundIt == m_vertices.end())
      {
        m_indices.push_back(m_vertices.size());
        m_vertices.push_back(vertex);
      }
      else
      {
        // vertex already exists, add its index
        m_indices.push_back(std::distance(m_vertices.begin(), foundIt));
      }

      m_AABB = m_AABB.AddPoint(vertex.m_pos);
    }
  }
}

// ------------------------------------------------------------------------------

std::vector<Vertex>& OBJModel::GetVertices() { return m_vertices; }

// ------------------------------------------------------------------------------

std::vector<std::uint32_t>& OBJModel::GetIndices() { return m_indices; }

// ------------------------------------------------------------------------------

math::AABB& OBJModel::GetAABB() { return m_AABB; }

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage