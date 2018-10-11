#include "ecs/ComponentMask.h"

namespace mage
{
namespace ecs
{

ComponentMask::ComponentMask()
    : m_componentBitMask(0)
{
}

void ComponentMask::OnAddComponent(std::uint32_t _componentTypeId) noexcept
{
    m_componentBitMask |= (1 << _componentTypeId);
}

void ComponentMask::OnRemoveComponent(std::uint32_t _componentTypeId) noexcept
{
    m_componentBitMask &= ~(1 << _componentTypeId);
}

bool ComponentMask::HasComponents(const ComponentMask &_mask) const noexcept
{
    return (m_componentBitMask & _mask.m_componentBitMask) == _mask.m_componentBitMask;
}

} // namespace ecs
} // namespace mage