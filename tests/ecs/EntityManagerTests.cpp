#include <catch.hpp>

#include "ecs/EntityManager.h"

SCENARIO("Entity Manager usage", "[ECS]")
{
  using namespace mage::ecs;

  GIVEN("An entity manager")
  {
    EntityManager manager;

    WHEN("A new entity is created")
    {
      Entity entity = manager.CreateEntity();

      THEN("The new entity is created with the first free index")
      {
        REQUIRE(entity.m_id == 0);
      }
    }

    WHEN("Multiple entities are added")
    {
      Entity entity1 = manager.CreateEntity();
      Entity entity2 = manager.CreateEntity();
      Entity entity3 = manager.CreateEntity();
      Entity entity4 = manager.CreateEntity();

      THEN("All the entities have a unique id")
      {
        REQUIRE(entity1.m_id == 0);
        REQUIRE(entity2.m_id == 1);
        REQUIRE(entity3.m_id == 2);
        REQUIRE(entity4.m_id == 3);
      }
    }

    WHEN("Entities are added when there are recycled indices")
    {
      Entity entity1 = manager.CreateEntity();
      Entity entity2 = manager.CreateEntity();
      manager.RecycleEntity(entity2);
      Entity entity21 = manager.CreateEntity();
      Entity entity3 = manager.CreateEntity();

      THEN("All the entities have a unique id")
      {
        REQUIRE(entity1.m_id == 0);
        REQUIRE(entity21.m_id == 1);
        REQUIRE(entity3.m_id == 2);
      }
    }
  }
}