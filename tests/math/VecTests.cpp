#include <catch/catch.hpp>

#include "math/Vec.h"

SCENARIO("Vector Math tests", "[Math]")
{
  using namespace mage::math;
  GIVEN("Two Vec2's")
  {
    Vec2f vec(1.0f, 1.0f);
    Vec2f vec2(1.0f, 1.0f);

    WHEN("They are added")
    {
      Vec2f result = vec + vec2;
      THEN("Result is equal to expected") { REQUIRE(result == Vec2f(2.0f)); }
    }

    WHEN("They are subtracted")
    {
      Vec2f result = vec - vec2;
      THEN("Result is equal to expected") { REQUIRE(result == Vec2f(0.0f)); }
    }

    WHEN("They are multiplied")
    {
      Vec2f result = vec * vec2;
      THEN("Result is equal to expected") { REQUIRE(result == Vec2f(1.0f)); }
    }

    WHEN("They are divided")
    {
      Vec2f result = vec / vec2;
      THEN("Result is equal to expected") { REQUIRE(result == Vec2f(1.0f)); }
    }

    WHEN("The dot product is used")
    {
      float result = vec.Dot(vec2);
      THEN("Result is equal to expected") { REQUIRE(result == 2.0f); }
    }

    WHEN("The magnitude is calculated")
    {
      float result = vec.GetMagnitude();
      THEN("Result is equal to expected") { REQUIRE(result == 1.41421356237f); }
    }

    WHEN("The vector is normalied")
    {
      Vec2f normalized = vec.GetNormalized();
      THEN("Result is equal to expected")
      {
        REQUIRE(normalized == Vec2f(1.0f / std::sqrtf(2)));
      }
    }

    WHEN("The distance is calculated")
    {
      float distance = vec.Distance(vec2);
      THEN("Result is equal to expected") { REQUIRE(distance == 0.0f); }
    }
  }

  GIVEN("One vec and one scalar")
  {
    Vec2f vec(1.0f, 1.0f);
    float scalar = 2.0f;

    WHEN("They are multiplied")
    {
      Vec2f result = vec * scalar;
      THEN("Result is equal to expected") { REQUIRE(result == Vec2f(2.0f)); }
    }

    WHEN("They are divided")
    {
      Vec2f result = vec / scalar;
      THEN("Result is equal to expected") { REQUIRE(result == Vec2f(0.5f)); }
    }
  }

  GIVEN("Two 3D Vecs")
  {
    Vec3f rightAxis(1.0f, 0.0f, 0.0f);
    Vec3f upAxis(0.0f, 1.0f, 0.0f);

    WHEN("The cross product for them is calculated")
    {
      Vec3f result = Cross(rightAxis, upAxis);
      THEN("Result is equal to expected")
      {
        Vec3f forwardAxis(0.0f, 0.0f, 1.0f);
        REQUIRE(result == forwardAxis);
      }
    }
  }
}