#include "ecs/Entity.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

Entity::Entity(std::int32_t _id)
    : m_id(_id)
{
}

// ------------------------------------------------------------------------------

bool Entity::operator==(const Entity& _other) const noexcept
{
  return m_id == _other.m_id;
}

// ------------------------------------------------------------------------------

bool Entity::operator!=(const Entity& _other) const noexcept
{
  return m_id != _other.m_id;
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage
