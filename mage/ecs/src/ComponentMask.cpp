#include "ecs/ComponentMask.h"

namespace mage
{
namespace ecs
{

ComponentMask::ComponentMask()
    : m_componentBitMask(0)
{
}

bool ComponentMask::HasComponents(const ComponentMask &_mask) const noexcept
{
    return (m_componentBitMask & _mask.m_componentBitMask) == _mask.m_componentBitMask;
}

} // namespace ecs
} // namespace mage