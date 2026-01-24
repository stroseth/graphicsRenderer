#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../saralib/vec3.h"

TEST_CASE("#1 - Dot Product")
{
    vec3 u = vec3(1,2,3);
    vec3 v = vec3(1,2,3);

    //There is definitely a better way to do this. I don't know why I'm doing it like this. shrug
    REQUIRE(u.e[0] == 1);
    REQUIRE(u.e[1] == 2);
    REQUIRE(u.e[2] == 3);
    
    REQUIRE(v.e[0] == 1);
    REQUIRE(v.e[1] == 2);
    REQUIRE(v.e[2] == 3);


    double ough = dot(u, v);
    float actualAnswer = 14;

    float eps = 1.0e-3;
    REQUIRE_THAT(ough, Catch::Matchers::WithinAbs(actualAnswer, eps));

}
/*
TEST_CASE("#2 - Cross Product")
{
    idk
}

TEST_CASE("#3 - ??? Product")
{
    idk
}

TEST_CASE("#4 - ?? Product")
{
    idk
}

TEST_CASE("#5 - ?? Product")
{
    idk
}
    */