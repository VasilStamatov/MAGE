#pragma once

#include "Component.h"

#include <cstdint>

namespace mage
{
namespace ecs
{

class ComponentMask
{
public:
  ComponentMask();

  template <typename ComponentType> void AddComponent() noexcept
  {
    m_componentBitMask |= (1 << GetComponentTypeId<ComponentType>());
  }

  template <typename ComponentType> void RemoveComponent() noexcept
  {
    m_componentBitMask &= (~(1 << GetComponentTypeId<ComponentType>()));
  }

  void Reset() noexcept;

  bool MatchesMask(ComponentMask _mask) const noexcept;

  bool HasComponent(std::uint32_t _componentTypeId) const noexcept;

private:
  std::uint32_t m_componentBitMask;
};

} // namespace ecs
} // namespace mage