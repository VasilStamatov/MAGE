#include <catch/catch.hpp>

#include "ecs/World.h"

struct TestComponent1 : mage::ecs::Component
{
};

struct TestComponent2 : mage::ecs::Component
{
};

struct TestComponent3 : mage::ecs::Component
{
};

class TestSystem : public mage::ecs::GameSystem
{
public:
  TestSystem()
  {
    m_systemSignature.AddComponent<TestComponent1>();
    m_systemSignature.AddComponent<TestComponent2>();
  }
  void Initialize(mage::ecs::World& _world) override {}
  void Uninitialize(mage::ecs::World& _world) override {}
  void Tick(mage::ecs::World& _world, float _deltaTime) override {}

  bool IsEntityRegistered(mage::ecs::Entity _entity)
  {
    return std::find(m_registeredEntities.begin(), m_registeredEntities.end(),
                     _entity) != m_registeredEntities.end();
  }
};

SCENARIO("System creation usage", "[ECS]")
{
  using namespace mage::ecs;
  GIVEN("A system, entity and a mask")
  {
    TestSystem system;
    Entity testEntity(0);
    ComponentMask testMask;

    WHEN("The mask matches the system signature and the system updates the "
         "entity status")
    {
      testMask.AddComponent<TestComponent1>();
      testMask.AddComponent<TestComponent2>();
      system.OnEntityComponentMaskChange(testEntity, testMask);

      THEN("The entity is registered in the system")
      {
        REQUIRE(system.IsEntityRegistered(testEntity));
      }
    }

    WHEN("The mask does not match the system signature and the system updates "
         "the entity status")
    {
      testMask.AddComponent<TestComponent1>();
      testMask.AddComponent<TestComponent3>();
      system.OnEntityComponentMaskChange(testEntity, testMask);

      THEN("The entity is not registered in the system")
      {
        REQUIRE_FALSE(system.IsEntityRegistered(testEntity));
      }
    }

    WHEN("The entity goes from matching to not matching and the system updates "
         "the entity status")
    {
      testMask.AddComponent<TestComponent1>();
      testMask.AddComponent<TestComponent2>();
      system.OnEntityComponentMaskChange(testEntity, testMask);

      testMask.RemoveComponent<TestComponent2>();
      system.OnEntityComponentMaskChange(testEntity, testMask);

      THEN("The entity is unregistered from the system")
      {
        REQUIRE_FALSE(system.IsEntityRegistered(testEntity));
      }
    }

    WHEN("The entity matches the system signature with more than what's "
         "required")
    {
      testMask.AddComponent<TestComponent1>();
      testMask.AddComponent<TestComponent2>();
      testMask.AddComponent<TestComponent3>();
      system.OnEntityComponentMaskChange(testEntity, testMask);

      THEN("The entity is registered in the system")
      {
        REQUIRE(system.IsEntityRegistered(testEntity));
      }
    }
  }
}