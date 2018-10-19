#include <catch/catch.hpp>

#include "ecs/Component.h"

struct TestComponent1 : mage::ecs::Component
{
};

struct TestComponent2 : mage::ecs::Component
{
};

struct TestComponent3 : mage::ecs::Component
{
};

TEST_CASE("Multiple Component id queries return the same unique id", "[ECS]")
{
  for (size_t i = 0; i < 2; i++)
  {
    std::int32_t firstId = mage::ecs::GetComponentTypeId<TestComponent1>();
    std::int32_t secondId = mage::ecs::GetComponentTypeId<TestComponent2>();
    std::int32_t thirdId = mage::ecs::GetComponentTypeId<TestComponent3>();

    REQUIRE(firstId == 0);
    REQUIRE(secondId == 1);
    REQUIRE(thirdId == 2);
  }
}