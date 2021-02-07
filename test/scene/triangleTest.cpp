#include <catch2/catch.hpp>
#include <glm/glm.hpp>

#include "scene/triangle.h"

void testPnts(glm::vec3 (&pnts)[3], Triangle &tri, bool ExpectHit = true);

TEST_CASE("Triangle Test", "[triangle]") {
  auto p0 = glm::vec3(0, 0, 0);
  auto p1 = glm::vec3(1, 0, 0);
  auto p2 = glm::vec3(0, 1, 0);
  Triangle tri(p0, p1, p2);

  auto normal = glm::vec3(0, 0, 1);
  REQUIRE(normal == tri.normal());
}

TEST_CASE("Intersection Hit Test", "[triangle]") {
  glm::vec3 v0(1, 0, 0);
  glm::vec3 v1(0, 0, 0);
  glm::vec3 v2(.5, .5, 0);
  glm::vec3 blue(0, 0, 1);
  Triangle tri(v0, v1, v2);
  tri.setColor(blue);

  // set the ray origin to the triangle centroid offset on the z-axis
  glm::vec3 origin(0.5, 0.17, -1);
  // make the z-axis direction positive.
  glm::vec3 direction(0, 0, 1);
  Ray ray(origin, direction);

  glm::vec3 expectedHit(0.5, 0.17, 0);
  Hit hit = tri.getRayIntersection(ray);
  REQUIRE(hit.isHit());
  REQUIRE(hit.position() == expectedHit);
  REQUIRE(hit.color() == blue);
}

void testPnts(glm::vec3 (&pnts)[3], Triangle &tri, bool ExpectHit) {
  Ray rays[3] = {};
  // make the z-axis direction positive.
  glm::vec3 direction(0, 0, 1);
  glm::vec3 expectedHit[3] = {};
  memcpy(expectedHit, pnts, sizeof(expectedHit));
  for (int i = 0; i < 3; i++) {
    pnts[i].z = -1;
    rays[i] = Ray(pnts[i], direction);
    Hit hit = tri.getRayIntersection(rays[i]);
    if (ExpectHit) {
      REQUIRE(hit.isHit());
      REQUIRE(hit.position() == expectedHit[i]);
      REQUIRE(hit.color() == tri.color());
    } else {
      REQUIRE(hit.isHit() == false);
    }
  }
}

TEST_CASE("Intersection Edge case Hit Test", "[triangle]") {
  glm::vec3 v0(1, 0, 0);
  glm::vec3 v1(0, 0, 0);
  glm::vec3 v2(.5, .5, 0);
  glm::vec3 blue(0, 0, 1);
  Triangle tri(v0, v1, v2);
  tri.setColor(blue);
  glm::vec3 pnts[3] = {glm::vec3(v0), glm::vec3(v1), glm::vec3(v2)};
  // test that the points of the triangle hit
  testPnts(pnts, tri);
  glm::vec3 m1((v0.x + v1.x) / 2.0, (v0.y + v1.y) / 2.0, 0);
  glm::vec3 m2((v0.x + v2.x) / 2.0, (v0.y + v2.y) / 2.0, 0);
  glm::vec3 m3((v1.x + v2.x) / 2.0, (v1.y + v2.y) / 2.0, 0);
  glm::vec3 mpnts[3] = {m1, m2, m3};

  // test that points on the edge hit
  testPnts(mpnts, tri);
}

glm::vec3 PerpendicularClockwise(const glm::vec3 &v) {
  return glm::vec3(v.y, -v.x, 0);
}

glm::vec3 genPnt(const glm::vec3 &direction, const glm::vec3 &pnt) {
  return pnt + direction;
}

TEST_CASE("Intersection Miss Test", "[triangle]") {
  glm::vec3 v0(1, 0, 0);
  glm::vec3 v1(0, 0, 0);
  glm::vec3 v2(.5, .5, 0);
  glm::vec3 blue(0, 0, 1);
  Triangle tri(v0, v1, v2);
  tri.setColor(blue);

  glm::vec3 m1((v0.x + v1.x) / 2.0, (v0.y + v1.y) / 2.0, 0);
  glm::vec3 m2((v0.x + v2.x) / 2.0, (v0.y + v2.y) / 2.0, 0);
  glm::vec3 m3((v1.x + v2.x) / 2.0, (v1.y + v2.y) / 2.0, 0);

  glm::vec3 e1 = v1 - v0;
  glm::vec3 e2 = v2 - v1;
  glm::vec3 e3 = v0 - v2;

  glm::vec3 pnts[3] = {genPnt(PerpendicularClockwise(e1), m1),
                       genPnt(PerpendicularClockwise(e2), m2),
                       genPnt(PerpendicularClockwise(e3), m3)};
  testPnts(pnts, tri, false);
}