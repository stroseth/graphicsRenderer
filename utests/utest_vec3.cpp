#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../saralib/vec3.h"

TEST_CASE("#1 - Dot Product")
{
    vec3 u = vec3(1,2,3);
    vec3 v = vec3(1,2,3);

    double ough = dot(u, v);
    float actualAnswer = 14;

    float eps = 1.0e-3;
    REQUIRE_THAT(ough, Catch::Matchers::WithinAbs(actualAnswer, eps));

}

TEST_CASE("#2 - Cross Product")
{
    vec3 u = vec3(7,1,25);
    vec3 v = vec3(1,27,6);

    vec3 ough = cross(u,v);
    vec3 actualAnswer = vec3(-669, -17, 188); 
    REQUIRE(ough.e[0] == actualAnswer.e[0]);
    REQUIRE(ough.e[1] == actualAnswer.e[1]);
    REQUIRE(ough.e[2] == actualAnswer.e[2]);

}

TEST_CASE("#3 - Unit Vector")
{
    vec3 u = vec3(1,2,3);
    double length = std::sqrt(14);

    vec3 ough = unit_vector(u);
    vec3 actualAnswer = vec3((1/length), (2/length), (3/length));
 
    REQUIRE(ough.e[0] == actualAnswer.e[0]);
    REQUIRE(ough.e[1] == actualAnswer.e[1]);
    REQUIRE(ough.e[2] == actualAnswer.e[2]);

}
 
TEST_CASE("#4 - Constructors")
{
    vec3 u = vec3(1,2,3);
    vec3 v = vec3(-19,4,403.3);

    //There is definitely a better way to do this. I don't know why I'm doing it like this. shrug
    REQUIRE(u.x()== 1);
    REQUIRE(u.y() == 2);
    REQUIRE(u.z()== 3);
    
    REQUIRE(v.e[0] == -19);
    REQUIRE(v.e[1] == 4);
    REQUIRE(v.e[2] == 403.3);

    vec3 defaultCons = vec3();

    REQUIRE(defaultCons.x() == 0);
    REQUIRE(defaultCons.y() == 0);
    REQUIRE(defaultCons.z() == 0);
}

TEST_CASE("#5 - Operators")
{
    vec3 u = vec3(9,-5,6);
    vec3 v = vec3(0,2.2,7);

    vec3 oughAdd = u + v;
    vec3 oughSub = u - v;
    vec3 oughMult = u * v;
    vec3 oughDiv = u/2;
    
    vec3 actAdd = vec3(9,-2.8,13);
    REQUIRE(oughAdd.e[0] == actAdd.e[0]);
    REQUIRE(oughAdd.e[1] == actAdd.e[1]);
    REQUIRE(oughAdd.e[2] == actAdd.e[2]);


    vec3 actSub = vec3(9,-7.2,-1);
    REQUIRE(oughSub.e[0] == actSub.e[0]);
    REQUIRE(oughSub.e[1] == actSub.e[1]);
    REQUIRE(oughSub.e[2] == actSub.e[2]);


    vec3 actMult = vec3(0,-11, 42);
    REQUIRE(oughMult.e[0] == actMult.e[0]);
    REQUIRE(oughMult.e[1] == actMult.e[1]);
    REQUIRE(oughMult.e[2] == actMult.e[2]);


    vec3 actDiv = vec3(4.5, -2.5, 3);
    REQUIRE(oughDiv.e[0] == actDiv.e[0]);
    REQUIRE(oughDiv.e[1] == actDiv.e[1]);
    REQUIRE(oughDiv.e[2] == actDiv.e[2]);

}
