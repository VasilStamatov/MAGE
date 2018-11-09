#include <catch.hpp>

#include "math/Quat.h"

SCENARIO("Quaternion Math tests", "[Math]")
{
  using namespace mage::math;

  GIVEN("Two Quats")
  {
    Quatf quat(1.0f, 0.0f, 0.0f, 1.0f);
    Quatf quat2(0.0f, 1.0f, 0.0f, 1.0f);

    WHEN("They are added")
    {
      Quatf result = quat + quat2;
      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(1.0f, 1.0f, 0.0f, 2.0f));
      }
    }

    WHEN("They are subtracted")
    {
      Quatf result = quat - quat2;
      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(1.0f, -1.0f, 0.0f, 0.0f));
      }
    }

    WHEN("They are multiplied")
    {
      Quatf result = quat * quat2;
      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(1.0f, 1.0f, 1.0f, 1.0f));
      }
    }

    WHEN("The dot product is used")
    {
      float result = quat.Dot(quat2);
      THEN("Result is equal to expected") { REQUIRE(result == 1.0f); }
    }
  }

  GIVEN("One quat and one scalar")
  {
    Quatf quat(1.0f, 2.0f, 3.0f, 1.0f);
    float scalar = 10.0f;

    WHEN("They are multiplied")
    {
      Quatf result = quat * scalar;

      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(10.0f, 20.0f, 30.0f, 10.0f));
      }
    }

    WHEN("Division is calculated")
    {
      Quatf result = quat / scalar;

      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(0.1f, 0.2f, 0.3f, 0.1f));
      }
    }
  }

  GIVEN("A single quat")
  {
    Quatf quat;

    WHEN("The quat is constructed by default")
    {
      THEN("It's initialized to an identity quat by default")
      {
        REQUIRE(quat == Quatf(0.0f, 0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("The magnitude is calculated")
    {
      float result = quat.GetMagnitude();
      THEN("Result is equal to expected") { REQUIRE(result == 1.0f); }
    }

    WHEN("The quat is normalized")
    {
      Quatf normalized = quat.GetNormalized();
      THEN("Result is equal to expected")
      {
        REQUIRE(normalized == Quatf(0.0f, 0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("The conjugate is calculated")
    {
      Quat quatToConjugate(1.0f, 1.0f, 0.0f, 1.0f);
      Quatf result = quatToConjugate.GetConjugated();
      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(-1.0f, -1.0f, 0.0f, 1.0f));
      }
    }

    WHEN("The inverse is calculated")
    {
      Quat quatToInverse(1.0f, 1.0f, 0.0f, 1.0f);
      Quatf result = quatToInverse.GetInversed();
      THEN("Result is equal to expected")
      {
        REQUIRE(result == Quatf(-0.33333f, -0.33333f, 0.0f, 0.33333f));
      }
    }
  }

  GIVEN("Quat generated from euler angles(radians)")
  {
    Quatf quat(Vec3f(ToRadians(90.0f), ToRadians(60.0f), ToRadians(30.0f)));

    WHEN("It's evaluated")
    {
      THEN("The quat contains expected values")
      {
        REQUIRE(quat == Quatf(0.5f, 0.5f, -0.183013f, 0.683013f));
      }
    }

    WHEN("The axis is calculated")
    {
      Vec3f axis = quat.GetAxis();
      THEN("The result is equal to expected")
      {
        REQUIRE(axis == Vec3f(0.68455f, 0.68455f, -0.250563f));
      }
    }

    WHEN("The euler angles are queried")
    {
      Vec3f eulerAngles = quat.ToEulerAngles();
      THEN("The resulting angles are equal to expected")
      {
        REQUIRE(eulerAngles ==
                Vec3f(ToRadians(90.0f), ToRadians(60.0f), ToRadians(30.0f)));
      }
    }
  }

  GIVEN("Quat Generated from rotation (origin and destination)")
  {
    Quatf quat =
        Quatf::GenRotation(Vec3f(0.0f, 1.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f));

    WHEN("It's evaluated")
    {
      THEN("The quat contains expected values")
      {
        REQUIRE(quat == Quatf(0.0f, 0.0f, -0.707107f, 0.707107f));
      }
    }
  }

  GIVEN("Quat Generated from rotation (angle and axis)")
  {
    Quatf quat = Quatf::GenRotation(ToRadians(60.0f), Vec3f(1.0f, 0.0f, 0.0f));

    WHEN("It's evaluated")
    {
      THEN("The quat contains expected values")
      {
        REQUIRE(quat == Quatf(0.5f, 0.0f, 0.0f, 0.866025f));
      }
    }
  }

  GIVEN("One generated rotation quat and one vec")
  {
    Quatf quat(Vec3f(ToRadians(90.0f), ToRadians(60.0f), ToRadians(30.0f)));
    Vec3f up(0.0f, 1.0f, 0.0f);

    WHEN("The vector is rotated using the quat")
    {
      Vec3f result = Quatf::RotateVec(quat, up);
      THEN("Result is equal to expected")
      {
        REQUIRE(result == Vec3f(0.75f, 0.433013f, 0.5f));
      }
    }
  }

  GIVEN("Quat constructed from mat4")
  {
    Quatf fromMat(GenRotationMat(ToRadians(60.0f), Vec3f(0.0f, 1.0f, 0.0f)));

    WHEN("The quat is calculated")
    {
      THEN("The result is equal to expected")
      {
        REQUIRE(fromMat == Quatf(0.0f, 0.5f, 0.0f, 0.866025f));
      }
    }
  }

  GIVEN("A single quat and a mat4")
  {
    Quatf quat(Vec3f(ToRadians(90.0f), ToRadians(30.0f), 0.0f));
    Mat4f mat;

    WHEN("The matrix is set to be the matrix version of a quat")
    {
      mat = quat.ToMat4();
      THEN("The matrix contains expected values for that quat")
      {
        float expected[16] = {0.866025f, 0.5f,         0.0f,          0.0f,
                              0.0f,      2.98023e-08f, -1.0f,         0.0f,
                              -0.5f,     0.866025f,    -2.98023e-08f, 0.0f,
                              0.0f,      0.0f,         0.0f,          1.0f};

        REQUIRE(mat == Mat4f(expected));
      }
    }
  }
}