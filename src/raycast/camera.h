
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"

class Camera {
private:
  glm::vec3 mOrigin, mDirection;
  float mFOV;
  glm::vec3 mUp;
  glm::vec3 mRight;

private:
  void recalculateOrientation();

public:
  Camera();
  Camera(glm::vec3 &o, glm::vec3 &d, float fov);

  const glm::vec3 &direction() const { return mDirection; }
  void setDirection(glm::vec3 &dir) { this->mDirection = dir; }

  const glm::vec3 &origin() const { return mOrigin; }
  void setOrigin(glm::vec3 &org) { this->mOrigin = org; }

  float getFOV() const { return mFOV; }
  void setFOV(float fovX) { this->mFOV = glm::radians(fovX); }

  const glm::vec3 &getUp() const { return mUp; }
  const glm::vec3 &getRight() const { return mRight; }
};

#endif // __CAMERA_H__
