#include "ray.h"

Ray::Ray(glm::vec3 &o, glm::vec3 &d)
    : mOrigin(o), mDirection(glm::normalize(d)) {}
Ray::Ray() : mOrigin(glm::vec3(0.0f)), mDirection(glm::vec3(0.0f)) {}

glm::vec3 Ray::point_at_dt(float dt) const { return mOrigin + dt * mDirection; }