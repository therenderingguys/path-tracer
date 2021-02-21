#include "scene/scene.h"
#include <catch2/catch.hpp>

TEST_CASE("Scene Add Triangle Test", "[scene][triangle]") {
  Camera cam;
  Scene scene(cam);

  scene.addTriangle({-0.5, -0.5, 0}, {0.5, -0.5, 0}, {0, 0.5, 0}, {1, 1, 1});
  scene.addTriangle({-0.5, -0.5, 0}, {0.5, -0.5, 0}, {0, 0.5, 0}, {1, 1, 1});
  scene.addTriangle({-0.5, -0.5, 0}, {0.5, -0.5, 0}, {0, 0.5, 0}, {1, 1, 1});

  REQUIRE(scene.getTriangleList().size() == 3);
}

TEST_CASE("Ray Intersect Scene Triangles Test", "[scene][triangle]") {
  Camera cam;
  Scene scene(cam);

  // id = 0
  scene.addTriangle({-0.5, -0.5, 0}, {0.5, -0.5, 0}, {0, 0.5, 0}, {1, 1, 1});
  // id = 1
  scene.addTriangle({-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0, 0.5, -0.5},
                    {1, 1, 1});
  // id = 2
  scene.addTriangle({-0.5, -0.5, -1}, {0.5, -0.5, -1}, {0, 0.5, -1}, {1, 1, 1});

  glm::vec3 rayOrg(0, 0, 0.5);
  glm::vec3 rayDir(0, 0, -1);
  Ray ray(rayOrg, rayDir);

  Hit hit = scene.getRayIntersection(ray);

  REQUIRE(hit.isHit());
  REQUIRE(hit.getTriId() == 0);
}