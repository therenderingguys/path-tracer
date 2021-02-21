#include "camera.h"

void Camera::recalculateOrientation() {
  glm::vec3 UP(0, 1, 0);
  if (glm::all(glm::equal(UP, mDirection))) {
    glm::vec3 RIGHT(1, 0, 0);
    mUp = glm::normalize(glm::cross(RIGHT, mDirection));
    mRight = glm::normalize(glm::cross(mDirection, mUp));
  } else {
    mRight = glm::normalize(glm::cross(mDirection, UP));
    mUp = glm::normalize(glm::cross(mRight, mDirection));
  }
}

Camera::Camera()
    : mOrigin({0, 0, 0}), mDirection({0, 0, -1}), mFOV(glm::radians(45.0f)),
      mUp(glm::vec3(0, 1, 0)) {
  recalculateOrientation();
}

Camera::Camera(glm::vec3 &o, glm::vec3 &d, float fov)
    : mOrigin(o), mFOV(glm::radians(fov)), mUp(glm::vec3(0, 1, 0)) {
  this->mDirection = glm::normalize(d);
  recalculateOrientation();
}
