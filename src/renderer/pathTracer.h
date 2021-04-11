/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __PATHTRACER_H__
#define __PATHTRACER_H__

#include <glm/glm.hpp>
#include <math.h>
#include <functional>
#include <memory>

#include "raycast/ray.h"
#include "scene/scene.h"
#include "renderer/pixelBuffer.h"

class PathTracer {
  typedef std::function<void()> drawCallBack;

private:
  const unsigned int mWidth, mHeight;
  std::unique_ptr<Scene> mScene;
  const float mAspectRatio;
  PixelBuffer *mPixelBuffer;
  drawCallBack mDrawCallBack;

private:
  glm::vec3 colorPixel(const unsigned int i, const unsigned int j,
                       Scene &scene);
  glm::vec3 colorRay(const Ray &ray, Scene &scene);

public:
  PathTracer(unsigned int width, unsigned int height);

  void renderScene(unsigned int width, unsigned int height, Scene &scene);

  void setPixelBuffer(PixelBuffer *pixelBuffer) { mPixelBuffer = pixelBuffer; };

  void setScene(Scene &scene) { mScene = std::make_unique<Scene>(scene); }

  drawCallBack getDrawCallBack() const { return mDrawCallBack; }
};

#endif // __PATHTRACER_H__
