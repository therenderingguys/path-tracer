// Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "PathTracer.h"

glm::vec3 PathTracer::colorPixel(const unsigned int i, const unsigned int j,
                               Scene &scene) {
  // maps float from one range to another
  auto map = [](float input, float oldMin, float oldMax, float newMin,
                float newMax) {
    float oldRange = oldMax - oldMin;
    float newRange = newMax - newMin;
    return ((input - oldMin) * newRange / oldRange) + newMin;
  };

  Camera &cam = scene.getCamera();
  float fov = cam.getFOV();

  // u and v are the coordiantes along the view plane that the pixel coordinates
  // (i and j) map to.
  float u = map((static_cast<float>(i)) + 0.5f, 0, mWidth, -1, 1);
  float v = map((static_cast<float>(j)) + 0.5f, 0, mHeight, 1, -1);

  // w is the distance the cameria is from th view plane which is defined by the
  // camera's field of view
  float w = 1.0f / glm::tan(fov / 2.0f);

  /*
   * p is the point in world space on the view plane that the ray will pass
   * through. we can calulcate p by summing its forward, right, and up
   * components in relation to the camera. Much like summing vectors (x, 0, 0) +
   * (0, y, 0) + (0, 0, z) to get point (x, y, z) except instead of summing in
   * camera space we will be summing in world space.
   *
   * Camera already hold's its own right, up, and direction vectors that
   * represent the camera's direction. The camera's direction represents the
   * forward vector in this case. All of these vectors are normalized.
   *
   * The u and v scalars previously calculated determin how far along these
   * vectors p exists. u and v are mapped between -1 and 1 where -1 represents
   * the left/bottom side of the viewplane and +1 represents the right/top side
   * of the viewplane. For example to get the right/left component of p we would
   * scale the camera's right vector by u (u * cam.getRight()). We would do this
   * for the up/down and forward/back component as well and sum those 3
   * components together to get the world space location of p.
   */
  glm::vec3 p = u * cam.getRight() + v * cam.getUp() + w * cam.direction();
  p += cam.origin();

  /*
   * To get the ray that will intersect p from the camera origin we subtract the
   * camera's origin position from p (p - camOrg) and set that as the direction
   * for the ray. This will ensure that the ray will intersect p if the camera
   * origin is set as the ray origin.
   */
  glm::vec3 rayOrg = cam.origin();
  glm::vec3 rayDir = p - rayOrg;
  Ray ray(rayOrg, rayDir);

  return colorRay(ray, scene);
}

glm::vec3 PathTracer::colorRay(const Ray &ray, Scene &scene) {
  Hit hit = scene.getRayIntersection(ray);
  return hit.color();
}

PathTracer::PathTracer(unsigned int width, unsigned int height)
    : mWidth(width), mHeight(height),
      mAspectRatio(static_cast<float>(width) / static_cast<float>(width)) {

  mDrawCallBack = [this]() { 
    renderScene(mWidth, mHeight, *mScene.get());
  };
}

void PathTracer::renderScene(unsigned int width, unsigned int height,
                           Scene &scene) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      glm::vec3 color = colorPixel(i, j, scene) * 255.0f;
      if (i == width-1 && j == height-1)
        color = glm::vec3(255, 255, 255);
      mPixelBuffer->setPixel(i, j, color);
    }
  }
}
