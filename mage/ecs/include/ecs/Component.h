#pragma once

#include <cstdint>

namespace mage
{
namespace ecs
{

namespace internal
{

std::uint32_t GenerateUniqueComponentId() noexcept;

} // namespace internal

struct Component
{
};

template <typename ComponentType>
std::uint32_t GetComponentTypeId() noexcept
{
    static_assert(std::is_base_of<Component, ComponentType>::value, "Must inherit from Component");
    static_assert(std::is_standard_layout<ComponentType>::value, "Must have standard layout (all members public, no virtual functions)");

    static std::uint32_t s_componentTypeId = GenerateUniqueComponentId();
    return s_componentTypeId;
}

} // namespace ecs
} // namespace mage