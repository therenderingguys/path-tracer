
#ifndef __HIT_H__
#define __HIT_H__

#include <glm/glm.hpp>

class Hit {
  bool mIsHit;
  glm::vec3 mPosition;
  glm::vec3 mColor;
  float mTime;
  unsigned int mTriId;

public:
  Hit();

  const glm::vec3 &position() const { return mPosition; }
  void setPosition(glm::vec3 p) { this->mPosition = p; }
  bool &isHit() { return mIsHit; }

  const glm::vec3 &color() const { return mColor; }
  void setColor(glm::vec3 c) { this->mColor = c; }
  void setTime(float t) { this->mTime = t; }
  float getTime() { return mTime; }
  void setTriId(unsigned int id) { this->mTriId = id; }
  unsigned int getTriId() const { return mTriId; }
};

#endif // __HIT_H__