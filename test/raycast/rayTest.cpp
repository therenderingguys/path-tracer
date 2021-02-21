#include <catch2/catch.hpp>
#include <glm/glm.hpp>

#include "raycast/ray.h"

TEST_CASE("Ray Test") {
  auto origin = glm::vec3(0.0f);
  auto direction = glm::vec3(0.0f, 0.5f, 0.0f);
  Ray ray(origin, direction);
  auto vec3Param = ray.point_at_dt(2.0f);
  auto answer = glm::vec3(0.0, 2.0, 0.0);
  REQUIRE(vec3Param == answer);
}