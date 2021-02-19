#include "renderer.h"

glm::vec3 Renderer::colorPixel(const unsigned int i, const unsigned int j,
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

  float u = map(((float)i) + 0.5f, 0, mWidth, -1, 1);
  float v = map(((float)j) + 0.5f, 0, mHeight, 1, -1);

  float w = 1.0f / tanf(fov / 2.0f);

  glm::vec3 p = u * cam.getRight() + v * cam.getUp() + w * cam.direction();

  glm::vec3 rayOrg = cam.origin();
  glm::vec3 rayDir = p - rayOrg;
  Ray ray(rayOrg, rayDir);

  return colorRay(ray, scene);
}

glm::vec3 Renderer::colorRay(const Ray &ray, Scene &scene) {
  Hit hit = scene.getRayIntersection(ray);
  return hit.color();
}

Renderer::Renderer(unsigned int width, unsigned int height)
    : mWidth(width), mHeight(height), mAspectRatio((float)width / height) {}

void Renderer::renderScene(unsigned int width, unsigned int height,
                           Scene &scene) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      glm::vec3 color = colorPixel(i, j, scene);
    }
  }
}
