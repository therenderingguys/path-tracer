#include <catch2/catch.hpp>
#include <glm/glm.hpp>

#include "camera.h"

TEST_CASE("Camera Test") {
  auto origin = glm::vec3(0.0f);
  auto direction = glm::vec3(0.0f, 2.0f, 0.0f);
  Camera camera(origin, direction);

  // check direction is normalized
  auto vec3Param = camera.direction();
  auto answer = glm::vec3(0.0, 1.0, 0.0);
  REQUIRE(vec3Param == answer);

  // generate ray
  auto ray = camera.generate_ray(1.0, 2.0);
  REQUIRE(ray.direction() == glm::vec3(1.0, 2.0, 0.0));
}