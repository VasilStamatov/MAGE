#include <catch.hpp>

#include "math/Mat.h"

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
      Mat4f transposed = GetTransposedMat(mat);
      THEN("Result is equal to expected")
      {
        REQUIRE(mage::math::Equals(transposed[1], mat[4], c_epsilon<float>));
        REQUIRE(mage::math::Equals(transposed[2], mat[8], c_epsilon<float>));
        REQUIRE(mage::math::Equals(transposed[6], mat[9], c_epsilon<float>));
        REQUIRE(mage::math::Equals(transposed[3], mat[12], c_epsilon<float>));
        REQUIRE(mage::math::Equals(transposed[7], mat[13], c_epsilon<float>));
        REQUIRE(mage::math::Equals(transposed[11], mat[14], c_epsilon<float>));
      }
    }

    WHEN("A translation matrix is generated")
    {
      Mat4f translate = GenTranslationMat(Vec3f(5.0f, 10.0f, 0.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(mage::math::Equals(translate[3], 5.0f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(translate[7], 10.0f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(translate[11], 0.0f, c_epsilon<float>));
      }
    }

    WHEN("A rotation matrix is generated")
    {
      Mat4f rotation = GenRotationMat(1.047198f, Vec3f(1.0f, 0.0f, 0.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(mage::math::Equals(rotation[5], 0.5f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(rotation[6], -0.866025f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(rotation[9], 0.866025f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(rotation[10], 0.5f, c_epsilon<float>));
      }
    }

    WHEN("A scaling matrix is generated")
    {
      Mat4f translate = GenScalingMat(Vec3f(5.0f, 10.0f, 1.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(mage::math::Equals(translate[0], 5.0f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(translate[5], 10.0f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(translate[10], 1.0f, c_epsilon<float>));
      }
    }

    WHEN("An ortho matrix is generated")
    {
      Mat4f ortho = GenOrthoMat(0.0f, 500.0f, 0.0f, 500.0f, 0.1f, 100.0f);
      THEN("Result is equal to expected")
      {
        REQUIRE(mage::math::Equals(ortho[0], 0.004f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(ortho[3], -1.0f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(ortho[5], 0.004f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(ortho[7], -1.0f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(ortho[10], -0.02002f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(ortho[11], -1.002f, c_epsilon<float>));
      }
    }

    WHEN("A perspective matrix is generated")
    {
      Mat4f perspective =
          GenPerspectiveMat(1.047198f, 1.77777777778f, 0.1f, 100.0f);
      THEN("Result is equal to expected")
      {
        REQUIRE(
            mage::math::Equals(perspective[0], 0.974278f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(perspective[5], 1.73205f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(perspective[10], -1.002f, c_epsilon<float>));
        REQUIRE(
            mage::math::Equals(perspective[11], -0.2002f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(perspective[14], -1.0f, c_epsilon<float>));
      }
    }

    WHEN("A LookAt matrix is generated")
    {
      Mat4f lookAt =
          GenLookAtMat(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(5.0f, 5.0f, 5.0f),
                       Vec3f(0.0f, 1.0f, 0.0f));
      THEN("Result is equal to expected")
      {
        REQUIRE(mage::math::Equals(lookAt[0], -0.707107f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[2], 0.707107f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[4], -0.408248f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[5], 0.816497f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[6], -0.408248f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[8], -0.57735f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[9], -0.57735f, c_epsilon<float>));
        REQUIRE(mage::math::Equals(lookAt[10], -0.57735f, c_epsilon<float>));
      }
    }
  }
}