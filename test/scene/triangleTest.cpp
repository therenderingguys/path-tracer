#include <catch2/catch.hpp>
#include <glm/glm.hpp>

#include "scene/triangle.h"

TEST_CASE("Triangle Test") {
  auto p0 = glm::vec3(0, 0, 0);
  auto p1 = glm::vec3(1, 0, 0);
  auto p2 = glm::vec3(0, 1, 0);
  Triangle tri(p0, p1, p2);

  auto normal = glm::vec3(0, 0, 1);
  REQUIRE(normal == tri.normal());
}