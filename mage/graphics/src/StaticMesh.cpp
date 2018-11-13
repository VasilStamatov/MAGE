#include "graphics/StaticMesh.h"

#include "exceptions/RuntimeError.h"
#include "math/Vec.h"

#include <unordered_map>

#include <tiny_obj_loader.h>

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

StaticMesh::StaticMesh(const std::string& _filepath)
    : m_vertexArrayObject()
    , m_vertexBuffer(BufferUsage::StaticDraw)
    , m_indexBufferObject()
{
  Load(_filepath);
}

// ------------------------------------------------------------------------------

void StaticMesh::Draw() const
{
  m_vertexArrayObject.Bind();
  m_indexBufferObject.Bind();
  m_vertexArrayObject.Draw(m_indexBufferObject.GetCount());
  m_indexBufferObject.Unbind();
  m_vertexArrayObject.Unbind();
}

// ------------------------------------------------------------------------------

void StaticMesh::Load(const std::string& _filepath)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                        _filepath.c_str()))
  {
    throw RUNTIME_ERROR(warn + err);
  }

  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;

  for (const auto& shape : shapes)
  {
    for (const auto& index : shape.mesh.indices)
    {
      Vertex vertex;

      vertex.m_pos[0] = attrib.vertices[3 * index.vertex_index + 0];
      vertex.m_pos[1] = attrib.vertices[3 * index.vertex_index + 1];
      vertex.m_pos[2] = attrib.vertices[3 * index.vertex_index + 2];

      vertex.m_color[0] = attrib.colors[3 * index.vertex_index + 0];
      vertex.m_color[1] = attrib.colors[3 * index.vertex_index + 1];
      vertex.m_color[2] = attrib.colors[3 * index.vertex_index + 2];

      vertex.m_texCoords[0] = attrib.texcoords[2 * index.texcoord_index + 0];
      vertex.m_texCoords[1] = attrib.texcoords[2 * index.texcoord_index + 1];

      vertex.m_normal[0] = attrib.normals[3 * index.normal_index + 0];
      vertex.m_normal[1] = attrib.normals[3 * index.normal_index + 1];
      vertex.m_normal[2] = attrib.normals[3 * index.normal_index + 2];

      // check if vertex doesn't exist
      auto foundIt = std::find(vertices.begin(), vertices.end(), vertex);
      if (foundIt == vertices.end())
      {
        indices.push_back(vertices.size());
        vertices.push_back(vertex);
      }
      else
      {
        // vertex already exists, add its index
        indices.push_back(std::distance(vertices.begin(), foundIt));
      }
    }
  }

  m_vertexBuffer.SetBufferData(sizeof(Vertex) * vertices.size(),
                               vertices.data());

  // setup the vao data layout (must be compliant with shader input attributes)
  GLBufferLayout bufferLayout;
  bufferLayout.PushFloat(3, false); // first 3 floats (m_position)
  bufferLayout.PushFloat(3, false); // last 3 floats (m_normals)
  bufferLayout.PushFloat(3, false); // second 3 floats (m_color)
  bufferLayout.PushFloat(2, false); // next 2 floats (m_texCoords)

  m_vertexArrayObject.AttachVertexBuffer(m_vertexBuffer, bufferLayout);

  m_indexBufferObject.SetData(indices.data(), indices.size());
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage