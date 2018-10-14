#include <catch/catch.hpp>

#include "ecs/ComponentMask.h"

SCENARIO("Component mask ", "[ECS]")
{
    using namespace mage::ecs;

    GIVEN("Component mask with one bit set")
    {
        ComponentMask mask;
        mask.SetComponentBit(5);

        WHEN("The mask is checked for that bit")
        {
            bool hasComponent = mask.HasComponent(5);
            THEN("The component mask returns true")
            {
                REQUIRE(hasComponent);
            }
        }

        WHEN("The bit is unset")
        {
            mask.UnsetComponentBit(5);

            THEN("Queries for that bit return false")
            {
                REQUIRE_FALSE(mask.HasComponent(5));
            }
        }

        WHEN("The same bit is set multiple times")
        {
            mask.SetComponentBit(5);
            mask.SetComponentBit(5);
            mask.SetComponentBit(5);

            THEN("The bit stays unchanged")
            {
                REQUIRE(mask.HasComponent(5));
            }
        }

        WHEN("The same bit is unset multiple times")
        {
            mask.UnsetComponentBit(5);
            mask.UnsetComponentBit(5);
            mask.UnsetComponentBit(5);

            THEN("The bit stays unchanged")
            {
                REQUIRE_FALSE(mask.HasComponent(5));
            }
        }

        WHEN("More component bits are added and then is compared to a mask which matches its components")
        {
            mask.SetComponentBit(0);
            mask.SetComponentBit(1);
            mask.SetComponentBit(2);

            ComponentMask secondMask;
            secondMask.SetComponentBit(1);
            secondMask.SetComponentBit(2);

            THEN("Checking if the first mask matches the second mask returns true")
            {
                REQUIRE(mask.ContainsBits(secondMask));
            }
        }

        WHEN("More component bits are added and then is compared to a mask which doesn't match its components")
        {
            mask.SetComponentBit(0);
            mask.SetComponentBit(1);
            mask.SetComponentBit(2);

            ComponentMask secondMask;
            secondMask.SetComponentBit(1);
            secondMask.SetComponentBit(2);
            secondMask.SetComponentBit(3);

            THEN("Checking if the first mask matches the second mask returns false")
            {
                REQUIRE_FALSE(mask.ContainsBits(secondMask));
            }
        }
    }
}