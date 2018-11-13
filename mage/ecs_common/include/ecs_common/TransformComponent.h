#pragma once

#include "ecs/Component.h"
#include "math/Transform.h"

namespace mage
{
namespace ecs
{
namespace common
{

// ------------------------------------------------------------------------------

struct TransformComponent : public ecs::Component
{
  math::Transform m_transform;
};

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage