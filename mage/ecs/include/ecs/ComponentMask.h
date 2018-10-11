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

    void OnAddComponent(std::uint32_t _componentTypeId) noexcept;
    void OnRemoveComponent(std::uint32_t _componentTypeId) noexcept;

    bool HasComponents(const ComponentMask &_mask) const noexcept;
};

} // namespace ecs
} // namespace mage