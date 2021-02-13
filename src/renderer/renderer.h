
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <glm/glm.hpp>

#include "scene/scene.h"

class Renderer {
private:
  glm::vec3 colorPixel(unsigned int i, unsigned int j, Scene &scene);

public:
  void renderScene(unsigned int width, unsigned int height, Scene &scene);
};

#endif // __RENDERER_H__
