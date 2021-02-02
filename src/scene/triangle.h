
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <glm/glm.hpp>

class Triangle {
  glm::vec3 mP0, mP1, mP2;
  glm::vec3 mNormal;

public:
  Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);
  
  const glm::vec3 &p0() const { return mP0; }
  const glm::vec3 &p1() const { return mP1; }
  const glm::vec3 &p2() const { return mP2; }

  const glm::vec3 &normal() const { return mNormal; }
};

#endif // __TRIANGLE_H__