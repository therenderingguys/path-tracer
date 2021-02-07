
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"

class Camera {
  glm::vec3 mOrigin, mDirection;

public:
  Camera(glm::vec3 &o, glm::vec3 &d);
  Ray generate_ray(float x, float y);
  const glm::vec3 &direction() const { return mDirection; }
  const glm::vec3 &origin() const { return mOrigin; }
};

#endif // __CAMERA_H__
