
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <glm/glm.hpp>

class Hit {
  bool mIsHit;
  glm::vec3 mPosition;
  glm::vec3 mColor;

public:
  Hit();

  const glm::vec3 &position() const { return mPosition; }
  void setPosition(glm::vec3 p) { this->mPosition = p; }

  const glm::vec3 &color() const { return mColor; }
  void setColor(glm::vec3 c) { this->mColor = c; }
};

#endif // __TRIANGLE_H__