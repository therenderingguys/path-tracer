#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <glm/glm.hpp>

#include "triangle.h"

class Scene
{
  unsigned int mTriangleCount;
	std::vector<Triangle> mTriangleList;

public:
  Scene() : mTriangleCount(0) {}

  const std::vector<Triangle> &getTriangleList() const { return mTriangleList; }
  void addTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color);
  Hit getRayIntersection(const Ray &ray);
};

#endif // __SCENE_H__
