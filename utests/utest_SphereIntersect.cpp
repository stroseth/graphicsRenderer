#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../saralib/Sphere.h"
#include "../saralib/ray.h"

TEST_CASE("Sphere Constructors"){
    Sphere s = Sphere();

    float eps = 1.0e-3;

    REQUIRE_THAT(s.getRadius(), Catch::Matchers::WithinAbs(1.0f, eps));
    REQUIRE(s.getCenter().x() == 0);
    REQUIRE(s.getCenter().y() == 0);
    REQUIRE(s.getCenter().z() == 0);
    REQUIRE(s.getColor().x() == 1.0);
    REQUIRE(s.getColor().y() == 1.0);
    REQUIRE(s.getColor().z() == 1.0);

    point3 c = point3(2.4f, 4.0f, -19);
    float r = 2.5f;

    Sphere s1 = Sphere(c, r);

    REQUIRE_THAT(s1.getRadius(), Catch::Matchers::WithinAbs(2.5f, eps));

    REQUIRE_THAT(s1.getCenter().x(), Catch::Matchers::WithinAbs(2.4f, eps));
    REQUIRE_THAT(s1.getCenter().y(), Catch::Matchers::WithinAbs(4.0f, eps));
    REQUIRE_THAT(s1.getCenter().z(), Catch::Matchers::WithinAbs(-19, eps));

}