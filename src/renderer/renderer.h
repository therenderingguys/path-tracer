
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <glm/glm.hpp>
#include <math.h>

#include "raycast/ray.h"
#include "scene/scene.h"

class Renderer {
private:
  const unsigned int mWidth, mHeight;
  const float mAspectRatio;

private:
  glm::vec3 colorPixel(const unsigned int i, const unsigned int j,
                       Scene &scene);
  glm::vec3 colorRay(const Ray &ray, Scene &scene);

public:
  Renderer(unsigned int width, unsigned int height);

  void renderScene(unsigned int width, unsigned int height, Scene &scene);
};

#endif // __RENDERER_H__
