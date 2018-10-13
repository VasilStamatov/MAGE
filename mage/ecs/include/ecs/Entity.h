#pragma once

#include <cstdint>

namespace mage
{
namespace ecs
{

struct Entity
{
    std::uint32_t m_id;

    Entity(std::uint32_t _id);

    bool operator==(const Entity &_other) const noexcept;
    bool operator!=(const Entity &_other) const noexcept;
};

} // namespace ecs
} // namespace mage