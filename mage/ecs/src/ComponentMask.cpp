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

void ComponentMask::Reset() noexcept { m_componentBitMask = 0; }

bool ComponentMask::MatchesMask(ComponentMask _mask) const noexcept
{
  return (m_componentBitMask & _mask.m_componentBitMask) ==
         _mask.m_componentBitMask;
}

bool ComponentMask::HasComponent(std::uint32_t _componentTypeId) const noexcept
{
  return ((m_componentBitMask & (1 << _componentTypeId)) != 0);
}

} // namespace ecs
} // namespace mage