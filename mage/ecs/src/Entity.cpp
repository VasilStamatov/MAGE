#include "../include/ecs/Entity.h"

namespace mage
{
namespace ecs
{

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
