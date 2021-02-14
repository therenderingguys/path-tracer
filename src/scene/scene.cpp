#include "scene.h"

void Scene::addTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2,
                        glm::vec3 color) {
  mTriangleList.push_back(Triangle(p0, p1, p2, color, mTriangleList.size()));
}

Hit Scene::getRayIntersection(const Ray &ray) {
  Hit hit;

  for (const Triangle &tri : mTriangleList) {
    Hit curHit = tri.getRayIntersection(ray);
    if (curHit.isHit() && curHit.getTime() < hit.getTime()) {
      hit = curHit;
    }
  }

  return hit;
}