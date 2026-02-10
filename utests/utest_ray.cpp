//Unit testing for ray class
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../saralib/ray.h"

TEST_CASE("#1 - Default Constructor")
{
    ray defaultRay = ray();

    float eps = 1.0e-3;
    float actualDefault = 0.0f;

    //origin
    REQUIRE_THAT(defaultRay.origin().x(), Catch::Matchers::WithinAbs(actualDefault, eps));
    REQUIRE_THAT(defaultRay.origin().y(), Catch::Matchers::WithinAbs(actualDefault, eps));
    REQUIRE_THAT(defaultRay.origin().z(), Catch::Matchers::WithinAbs(actualDefault, eps));

    //dir
    REQUIRE_THAT(defaultRay.direction().x(), Catch::Matchers::WithinAbs(actualDefault, eps));
    REQUIRE_THAT(defaultRay.direction().y(), Catch::Matchers::WithinAbs(actualDefault, eps));
    REQUIRE_THAT(defaultRay.direction().z(), Catch::Matchers::WithinAbs(actualDefault, eps));
}

TEST_CASE("#2 - Origin + Direction")
{
    point3 custOrig = point3();
    vec3 custDir = vec3(.2f,.6f,1.0f);
    ray customRay = ray(custOrig, custDir);

    float eps = 1.0e-3;

    REQUIRE_THAT(customRay.origin().x(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(customRay.origin().y(), Catch::Matchers::WithinAbs(0.0f, eps));
    REQUIRE_THAT(customRay.origin().z(), Catch::Matchers::WithinAbs(0.0f, eps));

    //dir
    REQUIRE_THAT(customRay.direction().x(), Catch::Matchers::WithinAbs(.2f, eps));
    REQUIRE_THAT(customRay.direction().y(), Catch::Matchers::WithinAbs(.6f, eps));
    REQUIRE_THAT(customRay.direction().z(), Catch::Matchers::WithinAbs(1.0f, eps));

}

TEST_CASE("#3 - Parametric Ray Equation")
{
    point3 custOrig = point3();
    vec3 custDir = vec3(.6f,.12f,1.0f);
    ray customRay = ray(custOrig, custDir);

    float eps = 1.0e-3;

    point3 ans = customRay.at(2.4);
    point3 actualAns = point3(1.44f,.288f,2.4f);

    REQUIRE_THAT(ans.x(), Catch::Matchers::WithinAbs(actualAns.x(), eps));
    REQUIRE_THAT(ans.y(), Catch::Matchers::WithinAbs(actualAns.y(), eps));
    REQUIRE_THAT(ans.z(), Catch::Matchers::WithinAbs(actualAns.z(), eps));
}