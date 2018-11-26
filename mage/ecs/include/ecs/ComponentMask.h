#pragma once

#include "Component.h"

#include <cstdint>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Component mask describes the different component types it holds. Each bit of
/// the 32 bit uint represents a component id where 0 means it doesn't have it
/// and 1 means it has that component.
/////////////////////////////////////////////////
class ComponentMask
{
public:
  ComponentMask();

  // ------------------------------------------------------------------------------

  template <typename ComponentType> void AddComponent() noexcept
  {
    m_componentBitMask |= (1 << GetComponentTypeId<ComponentType>());
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> void RemoveComponent() noexcept
  {
    m_componentBitMask &= (~(1 << GetComponentTypeId<ComponentType>()));
  }

  // ------------------------------------------------------------------------------

  void Reset() noexcept;

  /////////////////////////////////////////////////
  /// Checks to see if _mask's bitmask contains the components this mask has
  /////////////////////////////////////////////////
  bool MatchesMask(ComponentMask _mask) const noexcept;
  /////////////////////////////////////////////////
  /// Checks to see if this mask has component bit _componentTypeId
  /////////////////////////////////////////////////
  bool HasComponent(std::uint32_t _componentTypeId) const noexcept;

private:
  std::uint32_t m_componentBitMask;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage