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

/////////////////////////////////////////////////
/// The Transform component stores the transform of an entity
/////////////////////////////////////////////////
struct TransformComponent : public ecs::Component
{
  math::Transform m_transform;
};

// ------------------------------------------------------------------------------

} // namespace common
} // namespace ecs
} // namespace mage