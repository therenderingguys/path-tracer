/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __PATHTRACER_H__
#define __PATHTRACER_H__

#include <functional>
#include <glm/glm.hpp>
#include <math.h>
#include <memory>

#include "raycast/ray.h"
#include "renderer/pixelBuffer.h"
#include "scene/scene.h"

class PathTracer {
  typedef std::function<void()> drawCallBack;

private:
  std::unique_ptr<Scene> mScene;
  const float mAspectRatio;
  PixelBuffer *mPixelBuffer;
  void draw();

  glm::vec3 colorPixel(const unsigned int i, const unsigned int j);
  glm::vec3 colorRay(const Ray &ray);

public:
  PathTracer();

  void renderScene();

  void setPixelBuffer(PixelBuffer *pixelBuffer) { mPixelBuffer = pixelBuffer; };

  void setScene(std::unique_ptr<Scene> scene) { mScene = std::move(scene); }
  drawCallBack getDrawCallBack();
};

#endif // __PATHTRACER_H__
