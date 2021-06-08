// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "scene.h"

Scene::Scene(Camera &cam) : mCamera(cam) {}

void Scene::setCamera(glm::vec3 &pos, glm::vec3 &dir) {
  this->mCamera.setOrigin(pos);
  this->mCamera.setDirection(dir);
}

void Scene::addTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2,
                        glm::vec3 color) {
  mTriangleList.push_back(Triangle(p0, p1, p2, color, mTriangleList.size()));
}

void Scene::addLight(glm::vec3 direction) {
  mLightList.push_back(Light(direction));
}

Hit Scene::getRayIntersection(const Ray &ray) {
  Hit hit;

  for (const Triangle &tri : mTriangleList) {
    Hit curHit = tri.getRayIntersection(ray);
    if (curHit.isHit() && curHit.getTime() < hit.getTime()) {
      hit = curHit;
    }
  }
  glm::vec3 color{0, 0, 0};
  for (const Light &light : mLightList) {
    color += light.GetColor(mTriangleList[hit.getTriId()]);
  }
  if(mLightList.size() > 0) {
    hit.setColor(color);
  }
  return hit;
}