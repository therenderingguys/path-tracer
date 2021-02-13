#include "renderer.h"

#include "raycast/hit.h"

glm::vec3 Renderer::colorPixel(const unsigned int i, const unsigned int j, Scene &scene) {
  return glm::vec3();
}

void Renderer::renderScene(unsigned int width, unsigned int height, Scene &scene) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      glm::vec3 color = colorPixel(i, j, scene);
    }
  }
}
