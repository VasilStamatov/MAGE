#pragma once

#include <cstdint>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

namespace internal
{

std::int32_t GenerateUniqueComponentId() noexcept;

} // namespace internal

// ------------------------------------------------------------------------------

constexpr std::int32_t c_maxNumberOfComponentTypes = 32u;

// ------------------------------------------------------------------------------

struct Component
{
};

// ------------------------------------------------------------------------------

template <typename ComponentType> std::int32_t GetComponentTypeId() noexcept
{
  static_assert(std::is_base_of<Component, ComponentType>::value,
                "Must inherit from Component");
  static_assert(
      std::is_standard_layout<ComponentType>::value,
      "Must have standard layout (all members public, no virtual functions)");

  static std::int32_t s_componentTypeId = internal::GenerateUniqueComponentId();
  return s_componentTypeId;
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage