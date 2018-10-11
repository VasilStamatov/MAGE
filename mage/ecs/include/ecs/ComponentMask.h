#pragma once

#include "Component.h"

#include <cstdint>

namespace mage
{
namespace ecs
{

class ComponentMask
{
private:
  std::uint32_t m_componentBitMask;

public:
  ComponentMask();

  template <typename ComponentType>
  void AddComponent() noexcept
  {
    m_componentBitMask |= (1 << GetComponentTypeId<ComponentType>());
  }

  template <typename ComponentType>
  void RemoveComponent() noexcept
  {
    m_componentBitMask &= ~(1 << GetComponentTypeId<ComponentType>());
  }

  bool HasComponents(const ComponentMask &_mask) const noexcept;
};

} // namespace ecs
} // namespace mage