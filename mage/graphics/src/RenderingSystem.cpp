#include "graphics/RenderingSystem.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

RenderingSystem::RenderingSystem(GLShader _shader, RenderDevice& _renderDevice)
    : m_shader(std::move(_shader))
    , m_renderDevice(_renderDevice)
{
}

// ------------------------------------------------------------------------------

RenderingSystem::~RenderingSystem() {}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage