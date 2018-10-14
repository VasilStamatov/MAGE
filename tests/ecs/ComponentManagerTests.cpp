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
        TestComponent1 testComponent{55};
        ComponentManager<TestComponent1> componentManager;

        WHEN("A component is added to an entity")
        {
            componentManager.AddComponent(testEntity, testComponent);

            THEN("The stored component in the manager can be queried and used")
            {
                TestComponent1 *component = componentManager.GetComponent(testEntity);
                REQUIRE(component->m_data == testComponent.m_data);
            }
        }

        WHEN("A component is added to an entity multiple times")
        {
            componentManager.AddComponent(testEntity, testComponent);

            TestComponent1 testComponent2{100};

            componentManager.AddComponent(testEntity, testComponent2);

            THEN("The stored component is the first one added and subsequent adds do not modify it")
            {
                TestComponent1 *component = componentManager.GetComponent(testEntity);
                REQUIRE(component->m_data == testComponent.m_data);
            }
        }

        WHEN("A component is added and then removed")
        {
            componentManager.AddComponent(testEntity, testComponent);
            componentManager.RemoveComponent(testEntity);

            THEN("Querying for the component returns nullptr")
            {
                TestComponent1 *component = componentManager.GetComponent(testEntity);
                REQUIRE(component == nullptr);
            }
        }

        WHEN("A component is added and then removed multiple times")
        {
            componentManager.AddComponent(testEntity, testComponent);
            componentManager.RemoveComponent(testEntity);
            componentManager.RemoveComponent(testEntity);
            componentManager.RemoveComponent(testEntity);

            THEN("Additional removals are ignored and querying for the component returns nullptr")
            {
                TestComponent1 *component = componentManager.GetComponent(testEntity);
                REQUIRE(component == nullptr);
            }
        }
    }
}