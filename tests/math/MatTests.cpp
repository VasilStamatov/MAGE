#include <catch/catch.hpp>

#include "math/Mat.h"

#include <limits>

constexpr float epsilon = 0.00001f;

#define FloatEqual(_f1, _f2) std::abs(std::abs(_f1) - std::abs(_f2)) <= epsilon

SCENARIO("Matrix Math tests", "[Math]")
{
  using namespace mage::math;
  GIVEN("Two Mat4's")
  {
    Mat4f mat(1.0f);
    Mat4f mat2(1.0f);

    WHEN("They are added")
    {
      Mat4f result = mat + mat2;
      THEN("Result is equal to expected") { REQUIRE(result == Mat4f(2.0f)); }
    }

    WHEN("They are subtracted")
    {
      Mat4f result = mat - mat2;
      THEN("Result is equal to expected") { REQUIRE(result == Mat4f(0.0f)); }
    }

    WHEN("They are multiplied")
    {
      Mat4f result = mat * mat2;
      THEN("Result is equal to expected") { REQUIRE(result == Mat4f(1.0f)); }
    }
  }

  GIVEN("One Mat4 and one scalar")
  {
    Mat4f mat(1.0f);
    float scalar(2.0f);

    WHEN("They are multiplied")
    {
      Mat4f result = mat * scalar;
      THEN("Result is equal to expected") { REQUIRE(result == Mat4f(2.0f)); }
    }

    WHEN("They are divided")
    {
      Mat4f result = mat / scalar;
      THEN("Result is equal to expected") { REQUIRE(result == Mat4f(0.5f)); }
    }
  }

  GIVEN("One Mat4 and one vec4")
  {
    Mat4f mat(1.0f);
    Vec4f vec(5.0f);

    WHEN("They are multiplied")
    {
      Vec4f result = mat * vec;
      THEN("Result is equal to expected") { REQUIRE(result == Vec4f(5.0f)); }
    }
  }

  GIVEN("A single Mat4")
  {
    float matData[16] = {0.0f, 1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,
                         8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f};

    Mat4f mat(matData);

    WHEN("The transposed version of the mat is calculated")
    {
      Mat4f transposed = GetTransposed(mat);
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(transposed[1], mat[4]));
        REQUIRE(FloatEqual(transposed[2], mat[8]));
        REQUIRE(FloatEqual(transposed[6], mat[9]));
        REQUIRE(FloatEqual(transposed[3], mat[12]));
        REQUIRE(FloatEqual(transposed[7], mat[13]));
        REQUIRE(FloatEqual(transposed[11], mat[14]));
      }
    }

    WHEN("A translation matrix is generated")
    {
      Mat4f translate = GenTranslation(Vec3f(5.0f, 10.0f, 0.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(translate[3], 5.0f));
        REQUIRE(FloatEqual(translate[7], 10.0f));
        REQUIRE(FloatEqual(translate[11], 0.0f));
      }
    }

    WHEN("A rotation matrix is generated")
    {
      Mat4f rotation = GenRotation(1.047198f, Vec3f(1.0f, 0.0f, 0.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(rotation[5], 0.5f));
        REQUIRE(FloatEqual(rotation[6], -0.866025f));
        REQUIRE(FloatEqual(rotation[9], 0.866025f));
        REQUIRE(FloatEqual(rotation[10], 0.5f));
      }
    }

    WHEN("A scaling matrix is generated")
    {
      Mat4f translate = GenScaling(Vec3f(5.0f, 10.0f, 1.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(translate[0], 5.0f));
        REQUIRE(FloatEqual(translate[5], 10.0f));
        REQUIRE(FloatEqual(translate[10], 1.0f));
      }
    }

    WHEN("An ortho matrix is generated")
    {
      Mat4f ortho = GenOrtho(0.0f, 500.0f, 0.0f, 500.0f, 0.1f, 100.0f);
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(ortho[0], 0.004f));
        REQUIRE(FloatEqual(ortho[3], -1.0f));
        REQUIRE(FloatEqual(ortho[5], 0.004f));
        REQUIRE(FloatEqual(ortho[7], -1.0f));
        REQUIRE(FloatEqual(ortho[10], -0.02002f));
        REQUIRE(FloatEqual(ortho[11], -1.002f));
      }
    }

    WHEN("A perspective matrix is generated")
    {
      Mat4f perspective =
          GenPerspective(1.047198f, 1.77777777778f, 0.1f, 100.0f);
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(perspective[0], 0.974278f));
        REQUIRE(FloatEqual(perspective[5], 1.73205f));
        REQUIRE(FloatEqual(perspective[10], -1.002f));
        REQUIRE(FloatEqual(perspective[11], -0.2002f));
        REQUIRE(FloatEqual(perspective[14], -1.0f));
      }
    }

    WHEN("A LookAt matrix is generated")
    {
      Mat4f lookAt = GenLookAt(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(5.0f, 5.0f, 5.0f),
                               Vec3f(0.0f, 1.0f, 0.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(FloatEqual(lookAt[0], -0.707107f));
        REQUIRE(FloatEqual(lookAt[2], 0.707107f));
        REQUIRE(FloatEqual(lookAt[4], -0.408248f));
        REQUIRE(FloatEqual(lookAt[5], 0.816497f));
        REQUIRE(FloatEqual(lookAt[6], -0.408248f));
        REQUIRE(FloatEqual(lookAt[8], -0.57735f));
        REQUIRE(FloatEqual(lookAt[9], -0.57735f));
        REQUIRE(FloatEqual(lookAt[10], -0.57735f));
      }
    }
  }
}