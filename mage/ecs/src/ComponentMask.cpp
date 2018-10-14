#include "ecs/ComponentMask.h"

#include <assert.h>

namespace mage
{
namespace ecs
{

ComponentMask::ComponentMask()
    : m_componentBitMask(0)
{
}

void ComponentMask::SetComponentBit(std::uint32_t _componentBit) noexcept
{
    assert(_componentBit < 32);
    m_componentBitMask |= (1 << _componentBit);
}

void ComponentMask::UnsetComponentBit(std::uint32_t _componentBit) noexcept
{
    assert(_componentBit < 32);
    m_componentBitMask &= (~(1 << _componentBit));
}

void ComponentMask::Reset() noexcept
{
    m_componentBitMask = 0;
}

bool ComponentMask::ContainsBits(const ComponentMask &_mask) const noexcept
{
    return (m_componentBitMask & _mask.m_componentBitMask) == _mask.m_componentBitMask;
}

bool ComponentMask::HasComponent(std::uint32_t _componentBit) const noexcept
{
    assert(_componentBit < 32);
    return ((m_componentBitMask & (1 << _componentBit)) != 0);
}

} // namespace ecs
} // namespace mage