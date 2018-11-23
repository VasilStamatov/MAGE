#include "graphics/NullPostProcessPass.h"

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
  // FragColor = vec4(ex_TexCoord.x,ex_TexCoord.y, 1.0, 1.0);
}
)";

// ------------------------------------------------------------------------------

NullPostProcessPass::NullPostProcessPass()
    : PostProcessPass(GLShader(
          ShaderSourceCode{s_nullPassVertexShader, s_nullPassFragmentShader}))
{
}

// ------------------------------------------------------------------------------

NullPostProcessPass::~NullPostProcessPass() {}

// ------------------------------------------------------------------------------

void NullPostProcessPass::Apply(GLFramebuffer2D& _source,
                                GLFramebuffer2D* _target)
{
  if (_target != nullptr)
  {
    _target->Bind();
  }

  m_shader.Bind();

  _source.GetTexture().Bind(0);

  m_screenVAO.Bind();
  m_screenIBO.Bind();
  m_screenVAO.Draw(m_screenIBO.GetCount());
  m_screenIBO.Unbind();
  m_screenVAO.Unbind();

  _source.GetTexture().Unbind(0);

  if (_target != nullptr)
  {
    _target->Unbind();
  }
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage