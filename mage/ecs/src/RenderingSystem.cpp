#include "ecs/RenderingSystem.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

RenderingSystem::RenderingSystem(graphics::GLShader _shader)
    : m_shader(std::move(_shader))
{
}

// ------------------------------------------------------------------------------

RenderingSystem::~RenderingSystem() {}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage