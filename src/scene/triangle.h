
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <glm/glm.hpp>

#include "raycast/hit.h"
#include "raycast/ray.h"

class Triangle {
private:
  glm::vec3 mP0, mP1, mP2;
  glm::vec3 mNormal;
  glm::vec3 mColor;
  const size_t mId;

private:
  Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color,
           size_t id);

public:
  Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);
  Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color);

  static constexpr float EPSILON = 0.0000001f;

  const glm::vec3 &p0() const { return mP0; }
  const glm::vec3 &p1() const { return mP1; }
  const glm::vec3 &p2() const { return mP2; }

  const glm::vec3 &normal() const { return mNormal; }
  const glm::vec3 &color() const { return mColor; }

  size_t getId() const { return mId; }

  void setColor(glm::vec3 c) { mColor = c; }
  Hit getRayIntersection(const Ray &ray) const;

  friend class Scene;
};

#endif // __TRIANGLE_H__
