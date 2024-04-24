#include "catch.hpp"

#include <handy/Guard.h>

#include <optional>


using namespace ad;


SCENARIO("Guard base functionality.")
{
    GIVEN("A function.")
    {
        unsigned int callCount = 0;
        auto proof = [&callCount](){++callCount;};

        WHEN("A guard is instantiated for this function.")
        {
            {
                REQUIRE(callCount == 0);
                Guard guard{proof};

                THEN("The function is not called while the guard is in scope.")
                {
                    CHECK(callCount == 0);
                }
            }
            WHEN("The guard went out of scope.")
            {
                THEN("The function is called.")
                {
                    CHECK(callCount == 1);
                }
            }
        }
    }
}


SCENARIO("Guard move-ability.")
{
    GIVEN("A function.")
    {
        unsigned int callCount = 0;
        auto proof = [&callCount](){++callCount;};

        WHEN("A guard is instantiated for this function.")
        {
            REQUIRE(callCount == 0);
            std::optional<Guard> guard_A{proof};

            WHEN("The guard lifetime expires.")
            {
                guard_A.reset();
                THEN("The function is called.")
                {
                    REQUIRE_FALSE(guard_A.has_value());
                    CHECK(callCount == 1);
                }
            }

            WHEN("The initial guard (guard_A) is moved to another instance (guard_B).")
            {
                { // guard_B scope
                    std::optional<Guard> guard_B{std::move(*guard_A)};

                    WHEN("guard_A lifetime expires, but guard_B is still alive.")
                    {
                        guard_A.reset();
                        THEN("The function is not called.")
                        {
                            REQUIRE_FALSE(guard_A.has_value());
                            CHECK(callCount == 0);
                        }

                        WHEN("guard_B lifetime also expires.")
                        {
                            guard_B.reset();
                            THEN("The function is called.")
                            {
                                REQUIRE_FALSE(guard_B.has_value());
                                CHECK(callCount == 1);
                            }
                        }
                    }
                }

                WHEN("guard_B lifetime expires.")
                {
                    THEN("The function is called, even though guard_A is still alive.")
                    {
                        REQUIRE(guard_A.has_value());
                        CHECK(callCount == 1);
                    }
                }
            }
        }
    }
}


SCENARIO("ResourceGuard on built-in types.")
{
    GIVEN("A ResourceGuard for int, with a callback.")
    {
        unsigned int callCount = 0;
        const int guarded = 1658;
        auto callback = [&callCount, guarded](int aValue)
        {
            ++callCount;
            THEN("The callback receives the guarded value.")
            {
                CHECK(aValue == guarded);
            }
        };

        std::optional<ResourceGuard<int>> guard{std::in_place, guarded, callback};

        WHEN("The ResourceGuard lifetime expires.")
        {
            guard.reset();
            THEN("The callback is called.")
            {
                REQUIRE_FALSE(guard.has_value());
                CHECK(callCount == 1);
            }
        }

        WHEN("The ResourceGuard is released.") 
        {
            int value = guard->release();

            THEN("The guard value is returned.")
            {
                CHECK(value == guarded);
            }

            WHEN("The ResourceGuard lifetime expires.")
            {
                guard.reset();
                THEN("The callback is not called.")
                {
                    REQUIRE_FALSE(guard.has_value());
                    CHECK(callCount == 0);
                }
            }
        }
    }
}