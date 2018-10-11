#include "ecs/Entity.h"

namespace mage
{
namespace ecs
{

Entity::Entity(std::uint32_t _id)
    : m_iD(_id)
{
}

bool Entity::operator==(const Entity &_other) const noexcept
{
    return m_iD == _other.m_iD;
}

bool Entity::operator!=(const Entity &_other) const noexcept
{
    return m_iD != _other.m_iD;
}

} // namespace ecs
} // namespace mage
