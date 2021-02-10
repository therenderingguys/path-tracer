
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <glm/glm.hpp>

#include "raycast/hit.h"
#include "raycast/ray.h"

class Triangle {
  glm::vec3 mP0, mP1, mP2;
  glm::vec3 mNormal;
  glm::vec3 mColor;

  const unsigned int mId;

public:
  Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color, unsigned int id);

  static constexpr float EPSILON = 0.0000001f;

  const glm::vec3 &p0() const { return mP0; }
  const glm::vec3 &p1() const { return mP1; }
  const glm::vec3 &p2() const { return mP2; }

  const glm::vec3 &normal() const { return mNormal; }
  const glm::vec3 &color() const { return mColor; }

  const unsigned int getId() const { return mId; }

  void setColor(glm::vec3 c) { mColor = c; }
  Hit getRayIntersection(const Ray &ray) const;
};

#endif // __TRIANGLE_H__