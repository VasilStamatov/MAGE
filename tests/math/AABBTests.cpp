#include <catch/catch.hpp>

#include "math/AABB.h"

SCENARIO("AABB Intersection tests", "[Math]")
{
  using namespace mage::math;
  GIVEN("One AABB")
  {
    AABB first(Vec3f(-1.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f));

    WHEN("Intersection is checked with another AABB which does intersect it")
    {
      AABB second(Vec3f(0.0f, 0.5f, 0.5f), Vec3f(1.5f, 1.5f, 1.5f));

      bool intersects = first.Intersects(second);

      THEN("Intersection output is true") { REQUIRE(intersects); }
    }

    WHEN(
        "Intersection is checked with another AABB which does NOT intersect it")
    {
      AABB second(Vec3f(2.0f, 2.5f, 2.5f), Vec3f(4.5f, 5.5f, 5.5f));

      bool intersects = first.Intersects(second);

      THEN("Intersection output is false") { REQUIRE_FALSE(intersects); }
    }

    WHEN(
        "Another point is added in the AABB, which is less than the min extent")
    {
      AABB newAABB = first.AddPoint(Vec3f(-1.0f, -1.0f, -1.0f));

      THEN("The newAABB will have the new updated extent")
      {
        REQUIRE(newAABB.GetExtents() == Vec3f(1.0f));
      }
    }

    WHEN(
        "Another point is added in the AABB, which is more than the max extent")
    {
      AABB newAABB = first.AddPoint(Vec3f(2.0f, 2.0f, 2.0f));

      THEN("The newAABB will have the new updated extent")
      {
        REQUIRE(newAABB.GetExtents() == Vec3f(1.5f, 1.0f, 1.0f));
      }
    }
  }
}