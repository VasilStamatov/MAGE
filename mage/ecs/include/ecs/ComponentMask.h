#pragma once

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

  void SetComponentBit(std::uint32_t _componentBit) noexcept;
  void UnsetComponentBit(std::uint32_t _componentBit) noexcept;
  void Reset() noexcept;

  bool ContainsBits(const ComponentMask &_mask) const noexcept;
  bool HasComponent(std::uint32_t _componentBit) const noexcept;
};

} // namespace ecs
} // namespace mage