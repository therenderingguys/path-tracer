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
  const unsigned int mWidth, mHeight;
  std::unique_ptr<Scene> mScene;
  const float mAspectRatio;
  PixelBuffer *mPixelBuffer;
  const drawCallBack &mDrawCallBack = [this]() {
    renderScene(mWidth, mHeight, *mScene.get());
  };

private:
  glm::vec3 colorPixel(const unsigned int i, const unsigned int j,
                       Scene &scene);
  glm::vec3 colorRay(const Ray &ray, Scene &scene);

public:
  PathTracer(unsigned int width, unsigned int height);

  void renderScene(unsigned int width, unsigned int height, Scene &scene);

  void setPixelBuffer(PixelBuffer *pixelBuffer) { mPixelBuffer = pixelBuffer; };

  void setScene(Scene &scene) { mScene = std::make_unique<Scene>(scene); }

  const drawCallBack &getDrawCallBack() const { return mDrawCallBack; }
};

#endif // __PATHTRACER_H__
