#include <catch/catch.hpp>

#include "ecs/ComponentMask.h"

struct TestComponent1 : mage::ecs::Component
{
};

struct TestComponent2 : mage::ecs::Component
{
};

struct TestComponent3 : mage::ecs::Component
{
};

SCENARIO("Component mask ", "[ECS]")
{
  using namespace mage::ecs;

  GIVEN("Component mask with one bit set")
  {
    ComponentMask mask;
    mask.AddComponent<TestComponent1>();

    WHEN("The mask is checked for that bit")
    {
      bool hasComponent =
          mask.HasComponent(GetComponentTypeId<TestComponent1>());

      THEN("The component mask returns true") { REQUIRE(hasComponent); }
    }

    WHEN("The bit is unset")
    {
      mask.RemoveComponent<TestComponent1>();

      THEN("Queries for that bit return false")
      {
        REQUIRE_FALSE(mask.HasComponent(GetComponentTypeId<TestComponent1>()));
      }
    }

    WHEN("The same bit is set multiple times")
    {
      mask.AddComponent<TestComponent1>();
      mask.AddComponent<TestComponent1>();
      mask.AddComponent<TestComponent1>();

      THEN("The bit stays unchanged")
      {
        REQUIRE(mask.HasComponent(GetComponentTypeId<TestComponent1>()));
      }
    }

    WHEN("The same bit is unset multiple times")
    {
      mask.RemoveComponent<TestComponent1>();
      mask.RemoveComponent<TestComponent1>();
      mask.RemoveComponent<TestComponent1>();

      THEN("The bit stays unchanged")
      {
        REQUIRE_FALSE(mask.HasComponent(GetComponentTypeId<TestComponent1>()));
      }
    }

    WHEN("More component bits are added and then is compared to a mask which "
         "matches its components")
    {
      mask.AddComponent<TestComponent1>();
      mask.AddComponent<TestComponent2>();
      mask.AddComponent<TestComponent3>();

      ComponentMask secondMask;
      secondMask.AddComponent<TestComponent1>();
      secondMask.AddComponent<TestComponent2>();

      THEN("Checking if the first mask matches the second mask returns true")
      {
        REQUIRE(mask.MatchesMask(secondMask));
      }
    }

    WHEN("More component bits are added and then is compared to a mask which "
         "doesn't match its components")
    {
      mask.AddComponent<TestComponent1>();
      mask.AddComponent<TestComponent2>();

      ComponentMask secondMask;
      secondMask.AddComponent<TestComponent2>();
      secondMask.AddComponent<TestComponent3>();

      THEN("Checking if the first mask matches the second mask returns false")
      {
        REQUIRE_FALSE(mask.MatchesMask(secondMask));
      }
    }
  }
}