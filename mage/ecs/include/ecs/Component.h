#pragma once

#include <cstdint>

namespace mage
{
namespace ecs
{

namespace internal
{

std::uint32_t GenerateUniqueComponentId()
{
    static std::uint32_t s_UniqueComponentIdCounter = 0;
    return s_UniqueComponentIdCounter++;
}

} // namespace internal

struct Component
{
};

template <typename ComponentType>
std::uint32_t GetComponentTypeId()
{
    static_assert(std::is_base_of<Component, ComponentType>::value, "Must inherit from Component");
    static_assert(std::is_standard_layout<ComponentType>::value, "Must have standard layout (all members public, no virtual functions)");

    static std::uint32_t s_ComponentTypeId = GenerateUniqueComponentId();
    return s_ComponentTypeId;
}

} // namespace ecs
} // namespace mage