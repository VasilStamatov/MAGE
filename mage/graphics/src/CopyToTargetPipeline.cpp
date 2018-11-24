#include "graphics/CopyToTargetPipeline.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

static const char* s_nullPassVertexShader = R"(#version 330 core

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_TexCoord;

out vec2 ex_TexCoord;

void main()
{
  gl_Position = vec4(in_Position, 0, 1);
  ex_TexCoord = in_TexCoord;
}
)";

// ------------------------------------------------------------------------------

static const char* s_nullPassFragmentShader = R"(#version 330 core

uniform sampler2D in_Texture;

in vec2 ex_TexCoord;

out vec4 FragColor;

void main()
{
  vec4 tex = texture(in_Texture, ex_TexCoord);
  FragColor = tex;
}
)";

// ------------------------------------------------------------------------------

CopyToTargetPipeline::CopyToTargetPipeline()
    : m_nullPassShader(
          ShaderSourceCode{s_nullPassVertexShader, s_nullPassFragmentShader})
{
}

// ------------------------------------------------------------------------------

CopyToTargetPipeline::~CopyToTargetPipeline() {}

// ------------------------------------------------------------------------------

void CopyToTargetPipeline::Execute(GLFramebuffer2D& _source,
                                   GLFramebuffer2D& _target)
{
  m_nullPassShader.Bind();

  if (_source.GetTexture() == _target.GetTexture())
  {
    // If they are the same, assume that rendering to the screen is requested.
    _target.Unbind();
  }
  else
  {
    _target.Bind();
  }

  _source.GetTexture().Bind(0);

  m_screenVAO.Bind();
  m_screenIBO.Bind();
  m_screenVAO.DrawElements(m_screenIBO.GetCount());
  m_screenIBO.Unbind();
  m_screenVAO.Unbind();

  _source.GetTexture().Unbind(0);

  _target.Unbind();
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage