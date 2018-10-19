#include <catch/catch.hpp>

#include "ecs/ComponentManager.h"

struct TestComponent1 : mage::ecs::Component
{
  TestComponent1(std::uint32_t _data)
      : m_data(_data)
  {
  }
  std::uint32_t m_data;
};

SCENARIO("Component Manager functionality usage", "[ECS]")
{
  using namespace mage::ecs;
  GIVEN("Component manager, test entity and test component")
  {
    Entity testEntity(0);
    std::uint32_t dataForComponent = 34;
    ComponentManager<TestComponent1> componentManager;

    WHEN("A component is added to an entity")
    {
      componentManager.AddComponent(testEntity, dataForComponent);

      THEN("The stored component in the manager can be queried and used")
      {
        TestComponent1& component = componentManager.GetComponent(testEntity);
        REQUIRE(component.m_data == dataForComponent);
      }
    }

    WHEN("A component is added to an entity multiple times")
    {
      componentManager.AddComponent<TestComponent1>(testEntity,
                                                    dataForComponent);

      std::uint32_t otherData = 36;

      componentManager.AddComponent<TestComponent1>(testEntity, otherData);

      THEN("Subsequent adds don't modify the existing component")
      {
        TestComponent1& component = componentManager.GetComponent(testEntity);
        REQUIRE(component.m_data == dataForComponent);
      }
    }
  }
}