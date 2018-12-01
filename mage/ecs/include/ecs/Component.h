#pragma once

#include <cstdint>
#include <type_traits>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

namespace internal
{

/////////////////////////////////////////////////
/// Generates a unique conponent Id by incrementing each call
/////////////////////////////////////////////////
std::int32_t GenerateUniqueComponentId() noexcept;

} // namespace internal

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Number of max different component types the engine supports
/////////////////////////////////////////////////
constexpr std::int32_t c_maxNumberOfComponentTypes = 32u;

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// base component class to be inherited, only needed for ensuring
/// GetComponentTypeId is called only on Component types
/////////////////////////////////////////////////
struct Component
{
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// GetComponentTypeId returns a unique component Id for each unique type
/////////////////////////////////////////////////
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