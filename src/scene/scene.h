/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <glm/glm.hpp>
#include <vector>

#include "raycast/camera.h"
#include "triangle.h"

class Scene {
private:
  Camera &mCamera;
  std::vector<Triangle> mTriangleList;

public:
  Scene(Camera &cam);

  Camera &getCamera() const { return mCamera; }
  void setCamera(glm::vec3 &pos, glm::vec3 &dir);

  const std::vector<Triangle> &getTriangleList() const { return mTriangleList; }
  void addTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color);

  Hit getRayIntersection(const Ray &ray);
};

#endif // __SCENE_H__
