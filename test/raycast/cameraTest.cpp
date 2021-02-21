#include <catch2/catch.hpp>
#include <glm/glm.hpp>

#include "raycast/camera.h"

TEST_CASE("Camera Test", "[camera]") {
  auto origin = glm::vec3(0.0f);
  auto direction = glm::vec3(0.0f, 2.0f, 0.0f);
  Camera camera(origin, direction);

  // check direction is normalized
  auto vec3Param = camera.direction();
  auto answer = glm::vec3(0.0, 1.0, 0.0);
  REQUIRE(vec3Param == answer);
}

TEST_CASE("Camera Orientation Test", "[camera]") {
  Camera cam1;
  REQUIRE(cam1.getUp() == glm::vec3(0, 1, 0));
  REQUIRE(cam1.getRight() == glm::vec3(1, 0, 0));

  glm::vec3 org(0);
  glm::vec3 dir(0, 1, 0);
  Camera cam2(org, dir, 45.0f);
  REQUIRE(cam2.getUp() == glm::vec3(0, 0, 1));
  REQUIRE(cam2.getRight() == glm::vec3(1, 0, 0));
}